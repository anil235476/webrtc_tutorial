#include "desktop_capturer_callback.h"
#include <iostream>
#include <api/video/i420_buffer.h>
#include <third_party/libyuv/include/libyuv.h>
#include <cassert>

using namespace std;

using webrtc::DesktopCaptureOptions;
using webrtc::DesktopCapturer;

void desktop_capturer_callback::OnCaptureResult(webrtc::DesktopCapturer::Result result,
	std::unique_ptr<webrtc::DesktopFrame> frame) {

	const auto w = frame->size().width();
	const auto h = frame->size().height();

	rtc::scoped_refptr<webrtc::I420Buffer> frame_buffer =
		webrtc::I420Buffer::Create(w, h);

	const auto src_frame = frame->data();
	const size_t sample_size = 0;//todo: know about it
	const int crop_x = 0;
	const int crop_y = 0;
	const auto ret = libyuv::ConvertToI420(
		src_frame, sample_size,
		frame_buffer->MutableDataY(), frame_buffer->StrideY(),
		frame_buffer->MutableDataU(), frame_buffer->StrideU(),
		frame_buffer->MutableDataV(), frame_buffer->StrideV(),
		crop_x, crop_y,
		w, h,
		frame_buffer->width(), frame_buffer->height(),
		libyuv::kRotate0,
		libyuv::FOURCC_I420);

	assert(ret == 0);

}