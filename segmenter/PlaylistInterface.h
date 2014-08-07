/*
 * PlaylistInterface.h
 *
 *  Created on: Aug 7, 2014
 *      Author: satram
 */

#ifndef PLAYLISTINTERFACE_H_
#define PLAYLISTINTERFACE_H_

#include "segmenterCommon.h"

class PlaylistInterface {
public:
//	PlaylistInterface(){};
//	virtual ~PlaylistInterface();
	virtual void add_header(ConfigParams & config);
	virtual void add_header(variant_stream_info &stream_info);
	virtual void add_node();
	virtual void remove_node();
	virtual void publish_playlist();
	virtual void add_footer();
};

inline void PlaylistInterface::add_header(ConfigParams & config){}
inline void PlaylistInterface::add_header(variant_stream_info &stream_info){}
inline void PlaylistInterface::add_node(){}
inline void PlaylistInterface::remove_node(){}
inline void PlaylistInterface::publish_playlist(){}
inline void PlaylistInterface::add_footer(){}

#endif /* PLAYLISTINTERFACE_H_ */
