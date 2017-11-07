
#include <winsock2.h> //to remove compilation error
#include <iostream>
#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif
//#include "desktop_capturer_wrapper.h"
//#include "desktop_capturer_callback.h"
#include "rtc_base/sigslot.h"
#include "rtc_base/asyncudpsocket.h"
#include "rtc_base/thread.h"
#include <cassert>

using namespace std;
using namespace rtc;

// Generates a sequence of numbers (collaboratively).
class TestGenerator {
public:
	TestGenerator() : last(0), count(0) {}

	int Next(int prev) {
		int result = prev + last;
		last = result;
		count += 1;
		return result;
	}

	int last;
	int count;
};



struct TestMessage : public MessageData {
	explicit TestMessage(int v) : value(v) {}

	int value;
};

// Receives messages and sends on a socket.
class MessageClient : public MessageHandler, public TestGenerator {
public:
	MessageClient(Thread* pth, Socket* socket)
		: socket_(socket) {
	}

	~MessageClient() override { delete socket_; }

	void OnMessage(Message* pmsg) override {
		TestMessage* msg = static_cast<TestMessage*>(pmsg->pdata);
		int result = Next(msg->value);
		auto r = socket_->Send(&result, sizeof(result));
		assert(r > 0);
		//EXPECT_GE(socket_->Send(&result, sizeof(result)), 0);
		delete msg;
	}

private:
	Socket* socket_;
};


class socket_client : public sigslot::has_slots<> , public TestGenerator{

public:
	socket_client(AsyncSocket* socket, const SocketAddress& addr,
		Thread* post_thread, MessageHandler* phandler)
		: socket_(AsyncUDPSocket::Create(socket, addr)),
		post_thread_(post_thread),
		post_handler_(phandler) {
		socket_->SignalReadPacket.connect(this, &socket_client::OnPacket);
	}

	~socket_client() override { delete socket_; }

	SocketAddress address() const { return socket_->GetLocalAddress(); }

	void OnPacket(AsyncPacketSocket* socket, const char* buf, size_t size,
		const SocketAddress& remote_addr,
		const PacketTime& packet_time) {
		assert(size == sizeof(uint32_t));
		uint32_t prev = reinterpret_cast<const uint32_t*>(buf)[0];
		uint32_t result = Next(prev);

		post_thread_->PostDelayed(RTC_FROM_HERE, 200, post_handler_, 0,
			new TestMessage(result));
	}

private:
	AsyncUDPSocket* socket_;
	Thread* post_thread_;
	MessageHandler* post_handler_;
};

void test_thread() {
	const SocketAddress addr("127.0.0.1", 0);

	// Create the messaging client on its own thread.
	auto th1 = Thread::CreateWithSocketServer();
	Socket* socket =
		th1->socketserver()->CreateAsyncSocket(addr.family(), SOCK_DGRAM);
	MessageClient msg_client(th1.get(), socket);

	// Create the socket client on its own thread.
	auto th2 = Thread::CreateWithSocketServer();
	AsyncSocket* asocket =
		th2->socketserver()->CreateAsyncSocket(addr.family(), SOCK_DGRAM);
	socket_client sock_client(asocket, addr, th1.get(), &msg_client);

	socket->Connect(sock_client.address());

	th1->Start();
	th2->Start();

	// Get the messages started.
	th1->PostDelayed(RTC_FROM_HERE, 100, &msg_client, 0, new TestMessage(1));

	// Give the clients a little while to run.
	// Messages will be processed at 100, 300, 500, 700, 900.
	Thread* th_main = Thread::Current();
	th_main->ProcessMessages(1000);

	// Stop the sending client. Give the receiver a bit longer to run, in case
	// it is running on a machine that is under load (e.g. the build machine).
	th1->Stop();
	th_main->ProcessMessages(200);
	th2->Stop();

	//// Make sure the results were correct
	//EXPECT_EQ(5, msg_client.count);
	//EXPECT_EQ(34, msg_client.last);
	//EXPECT_EQ(5, sock_client.count);
	//EXPECT_EQ(55, sock_client.last);
}

int main() {
	cout << "hi\n";
	test_thread();
	/*desktop_capturer_wrapper capturer;
	desktop_capturer_callback callback;
	capturer.start(&callback);
	capturer.capture();*/
	return 0;
}