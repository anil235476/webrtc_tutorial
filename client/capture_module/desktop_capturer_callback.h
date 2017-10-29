#ifndef _DESKTOP_CATPTURER_CALLBACK_
#define _DESKTOP_CATPTURER_CALLBACK_
#include <winsock2.h> //to remove compilation error
#include "modules/desktop_capture/desktop_capturer.h"

class desktop_capturer_callback : public webrtc::DesktopCapturer::Callback {
public:

	/**DesktopCapturer::callback implementation*/
	void OnCaptureResult(webrtc::DesktopCapturer::Result result,
		std::unique_ptr<webrtc::DesktopFrame> frame) override;
	/********************************************/
};


#endif//_DESKTOP_CATPTURER_CALLBACK_