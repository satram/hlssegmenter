/*
 * MasterPlaylist.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "MasterPlaylist.h"

MasterPlaylist::MasterPlaylist() {
	// TODO Auto-generated constructor stub

}

MasterPlaylist::~MasterPlaylist() {
	// TODO Auto-generated destructor stub
}

void MasterPlaylist::remove_node()
{
}



void MasterPlaylist::add_header(ConfigParams & config)
{
	Section header("header");
	header.add_tag("M3U");
	header.add_tag("VERSION", 3);
	playlist.add_section(header);

	{
		Section node("n1");
		Tag t("STREAM-INF");
		t.add_property("BANDWIDTH", 512000);
		t.add_property("RESOLUTION","1280x720");
		t.add_property("CODECS","\"avc1.42001f,mp4a.40.2\"");
		node.add_tag(t);
		node.set_path("http://192.168.1.254:8080/hlsserver/");
		node.set_locator("media.m3u8");
		playlist.add_section(node);
	}

	{
		Section node("n1");
		Tag t("I-FRAME-STREAM-INF");
		t.add_property("BANDWIDTH", 512000);
		t.add_property("RESOLUTION","1280x720");
		t.add_property("CODECS","\"avc1.42001f,mp4a.40.2\"");
		t.add_property("URI","http://192.168.1.254:8080/hlsserver/iframe.m3u8");
		node.add_tag(t);
		playlist.add_section(node);
	}
}



void MasterPlaylist::publish_playlist()
{
	std::cout << "-----------------Master playlist-----------------" << std::endl;
	std::cout << playlist.marshall();
}



void MasterPlaylist::add_node()
{
}



void MasterPlaylist::add_header(variant_stream_info & stream_info)
{
}

void MasterPlaylist::add_footer()
{
}




