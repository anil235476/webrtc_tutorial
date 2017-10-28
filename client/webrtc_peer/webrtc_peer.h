#ifndef _WEBRTC_PEER_H__
#define _WEBRTC_PEER_H__
#include <vector>
#include "common_def.h"

namespace webrtc_peer {

	peer_id_type create_peer_connection(const turn_addresses_list& turn_addresses);
	void close_peer_connection(const peer_id_type& id);

}//namespace webrtc_peer


#endif//_WEBRTC_PEER_H__
