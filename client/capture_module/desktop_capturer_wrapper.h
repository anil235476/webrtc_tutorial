#ifndef _DESKTOP_CAPTURER_WRAPPER_H_
#define _DESKTOP_CAPTURER_WRAPPER_H_
#include <winsock2.h> //to remove compilation error
#include "modules/desktop_capture/desktop_capturer.h"

class desktop_capturer_wrapper : public webrtc::DesktopCapturer::Callback {
private:

	std::unique_ptr<webrtc::DesktopCapturer> capturer_;
	//webrtc::DesktopCapturer::Callback* callback_{ nullptr };
public:
	desktop_capturer_wrapper();
	~desktop_capturer_wrapper();

	void start(webrtc::DesktopCapturer::Callback*);
	void capture();

	/**DesktopCapturer::callback implementation*/
	void OnCaptureResult(webrtc::DesktopCapturer::Result result,
		std::unique_ptr<webrtc::DesktopFrame> frame) override;
	/********************************************/
};

#endif