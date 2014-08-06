/*
 * MediaPlaylist.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "MediaPlaylist.h"

MediaPlaylist::MediaPlaylist() {
	// TODO Auto-generated constructor stub

}

MediaPlaylist::~MediaPlaylist() {
	// TODO Auto-generated destructor stub
}

void MediaPlaylist::publish_playlist()
{
	Section header("header");
	header.add_tag("M3U");
	header.add_tag("VERSION", 3);
	header.add_tag("PLAYLIST-TYPE", "EVENT");
	header.add_tag("TARGETDURATION", 8);
	header.add_tag("MEDIA-SEQUENCE", 0);
	media_playlist.add_section(header);

	std::cout << media_playlist.marshall();

}


