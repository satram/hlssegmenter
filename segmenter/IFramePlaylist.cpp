/*
 * IFramePlaylist.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "IFramePlaylist.h"

IFramePlaylist::IFramePlaylist() {
	// TODO Auto-generated constructor stub

}

IFramePlaylist::~IFramePlaylist() {
	// TODO Auto-generated destructor stub
}

void IFramePlaylist::add_header(ConfigParams & config)
{
}

void IFramePlaylist::publish_playlist()
{
	std::cout << "-----------------IFrames playlist-----------------" << std::endl;
	std::cout << playlist.marshall();
}



void IFramePlaylist::add_node()
{
}



void IFramePlaylist::add_header(variant_stream_info &stream_info)
{
	if (stream_info.generate_iframe_url)
	{
		Section header("header");
		header.add_tag("M3U");
		header.add_tag("VERSION", 4);
		header.add_tag("I-FRAMES-ONLY");
		playlist.add_section(header);
	}
}

void IFramePlaylist::add_footer()
{

}

void IFramePlaylist::remove_node()
{
}


