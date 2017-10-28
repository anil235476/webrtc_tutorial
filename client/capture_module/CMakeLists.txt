cmake_minimum_required(VERSION 3.1)

project(capture_module)

#set( webrtc_dir 
#$ENV{WEBRTC_DIR}
#)
message( STATUS
"webrtc dirctory: $ENV{WEBRTC_DIR}"
)

message(STATUS 
	"webrtc lib dircotr: $ENV{WEBRTC_LIB_DIR}"
)

if(WIN32)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

add_definitions(-DWEBRTC_WIN)
include_directories(
	$ENV{WEBRTC_DIR}
)

link_directories(
	$ENV{WEBRTC_LIB_DIR}
)


add_executable( capture_module
		main.cxx
		desktop_capturer_wrapper.h
		desktop_capturer_wrapper.cxx
		
)

target_link_libraries(capture_module
	webrtc
	Winmm
	d3d11
	DXGI
	Ws2_32
)