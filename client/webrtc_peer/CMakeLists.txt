cmake_minimum_required(VERSION 3.1)

project(webrtc_peer)

#set( webrtc_dir 
#$ENV{WEBRTC_DIR}
#)
message( STATUS
"webrtc dirctory: $ENV{WEBRTC_DIR}"
)

include_directories(
	$ENV{WEBRTC_DIR}
)

add_library( webrtc_peer
plugin_api.h
webrtc_peer.h
webrtc_peer.cxx
simple_peer_connection.cc
simple_peer_connection.h
common_def.h
)