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
	var1.id = "child1";
	var1.bandwidth = 52000;
	var1.generate_iframe_url = true;
	var1.vid.codec = h264video;
	var1.vid.profile = "baseline";
	var1.vid.level = 3.1;
	var1.aud.codec = mpeg2audio_adts;
	var1.aud.subtype = "aac-lc";

	config.add_variant(var1);

	HlsPlaylistGenerator hlswrapper;
	hlswrapper.test_playlist_gen(config);


	config.remove_variant("child1");


	return 0;
}
