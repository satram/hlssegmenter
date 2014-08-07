/*
 * testMain.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "segmenterCommon.h"


int main()
{
	ConfigParams config;

	variant_stream_info var1;
	var1.id = "quality1";
	var1.bandwidth = 52000;
	var1.generate_iframe_url = true;
	var1.vid.codec = h264video;
	var1.vid.profile = "baseline";
	var1.vid.level = 3.1;
	var1.vid.resolution = "1920x1080";
	var1.aud.codec = mpeg4audio_latm;
	var1.aud.subtype = "aac-lc";
	var1.playlist_type = event;
	var1.segment_duration = 3.0;
	var1.web_server_loc = "http://192.168.1.10:8081/hlschunks/";

	config.add_variant(var1);

	HlsPlaylistGenerator hlswrapper;
	hlswrapper.test_playlist_gen(config);


	config.remove_variant("child1");


	return 0;
}
