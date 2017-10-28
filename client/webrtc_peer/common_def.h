#ifndef _WEBRTC_COMMON_DEF_H
#define _WEBRTC_COMMON_DEF_H
#include <string>
#include <vector>

namespace webrtc_peer {

	using peer_id_type = int;

	struct turn_address {
		std::string url_;
		std::string usr_name_;
		std::string password_;
	};

	using turn_addresses_list = std::vector<turn_address>;
}//namespace webrtc_peer 
#endif//_WEBRTC_COMMON_DEF_H