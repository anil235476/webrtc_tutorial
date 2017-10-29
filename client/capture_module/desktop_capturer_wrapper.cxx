
#include "desktop_capturer_wrapper.h"
#include "modules/desktop_capture/desktop_capture_options.h"
#include <iostream>
#include <cassert>

using namespace std;

using webrtc::DesktopCaptureOptions;
using webrtc::DesktopCapturer;

desktop_capturer_wrapper::desktop_capturer_wrapper()
{
	DesktopCaptureOptions options(DesktopCaptureOptions::CreateDefault());
	capturer_ = DesktopCapturer::CreateScreenCapturer(options);
}

desktop_capturer_wrapper::~desktop_capturer_wrapper() = default;

void desktop_capturer_wrapper::start(webrtc::DesktopCapturer::Callback* ptr) {
	//assert(ptr);
	if (ptr)
		capturer_->Start(ptr);
	else
		capturer_->Start(this);
}

void desktop_capturer_wrapper::capture() {
	capturer_->CaptureFrame();
}

void desktop_capturer_wrapper::OnCaptureResult(webrtc::DesktopCapturer::Result result,
	std::unique_ptr<webrtc::DesktopFrame> frame) {
	cout << "capture result\n";
	cout << "height = " << frame->size().height() << endl;
	cout << "width = " << frame->size().width() << endl;
}

