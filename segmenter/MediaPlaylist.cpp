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

void MediaPlaylist::add_header(variant_stream_info &stream_info)
{
	Section header("header");
	header.add_tag("M3U");
	header.add_tag("VERSION", 3);
	header.add_tag("MEDIA-SEQUENCE", 0);
	playlist.add_section(header);
}

void MediaPlaylist::add_node()
{
}

void MediaPlaylist::remove_node()
{
}

void MediaPlaylist::add_header(ConfigParams & config)
{
	Section header = playlist.get_section("header");
	if(config.playlist_type == event)
		header.add_tag("PLAYLIST-TYPE", "EVENT");
	else if(config.playlist_type == vod)
		header.add_tag("PLAYLIST-TYPE", "VOD");
	header.add_tag("TARGETDURATION", config.segment_duration);
	playlist.modify_section(header);
}

void MediaPlaylist::publish_playlist()
{
	std::cout << "-----------------Media playlist-----------------" << std::endl;
	std::cout << playlist.marshall();
}

void MediaPlaylist::add_footer()
{
}

