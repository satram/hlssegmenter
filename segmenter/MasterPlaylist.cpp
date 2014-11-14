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


void MasterPlaylist::add_header(HlsConfigParams & config)
{
	Section header("header");
	header.add_tag("M3U");
	//header.add_tag("VERSION", 3);
	playlist.add_section(header);

	for(auto it = config.variant_streams.begin(), ite= config.variant_streams.end(); it != ite; it++)
	{
		std::ostringstream oss;
		oss << "\"";
		if(it->vid.codec == h264video)
			oss << "avc1";

		//profile
		if(it->vid.profile == "baseline")
			oss << ".4200";
		else if(it->vid.profile == "main")
			oss << ".4d00";
		else if(it->vid.profile == "high")
			oss << ".6400";

		//level
		if(it->vid.level == 3.0)
			oss << "1e";
		else if(it->vid.level == 3.1)
			oss << "1f";

		//audio
		if(it->aud.codec == mpeg4audio_latm && it->aud.subtype == "aac-lc")
			oss << ",mp4a.40.2";
		else if(it->aud.codec == mpeg2audio_adts && it->aud.subtype == "aac-lc")
			oss << ",mp4a.20.2";
		oss << "\"";

		{
			Section node("n1");
			Tag t("STREAM-INF");
			t.add_property("BANDWIDTH", it->bandwidth);
			t.add_property("RESOLUTION",it->vid.resolution);
			t.add_property("CODECS",oss.str());
			node.add_tag(t);
			node.set_path((config.web_server_url + it->id).c_str());
			node.set_locator("media.m3u8");
			playlist.add_section(node);
		}

		{
			Section node("n1");
			Tag t("I-FRAME-STREAM-INF");
			t.add_property("BANDWIDTH", it->bandwidth/10);
			t.add_property("RESOLUTION",it->vid.resolution);
			t.add_property("CODECS",oss.str());
			oss.str("");
			oss << "\"" << config.web_server_url ;
			if(!config.web_server_url.empty() && config.web_server_url.find_last_of("/") != (config.web_server_url.size()-1))
				oss << "/" ;
			oss << it->id << "/iframe.m3u8\"";
			t.add_property("URI", oss.str());
			node.add_tag(t);
			playlist.add_section(node);
		}
	}
}





