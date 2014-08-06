/*
 * IFramePlaylist.h
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#ifndef IFRAMEPLAYLIST_H_
#define IFRAMEPLAYLIST_H_

#include "segmenterCommon.h"

class IFramePlaylist {

	Playlist iframe_playlist;

public:
	IFramePlaylist();
	virtual ~IFramePlaylist();
	void add_header();
	void add_node();
	void remove_node();
	void publish_playlist();
};

#endif /* IFRAMEPLAYLIST_H_ */
