/*
 * MediaPlaylist.h
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#ifndef MEDIAPLAYLIST_H_
#define MEDIAPLAYLIST_H_

#include "segmenterCommon.h"

class MediaPlaylist {

	Playlist media_playlist;

public:
	MediaPlaylist();
	virtual ~MediaPlaylist();

	void add_header();
	void add_node();
	void remove_node();
	void publish_playlist();
};

#endif /* MEDIAPLAYLIST_H_ */
