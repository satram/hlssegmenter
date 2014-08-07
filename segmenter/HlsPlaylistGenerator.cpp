	/*
 * HlsPlaylistGenerator.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "HlsPlaylistGenerator.h"

HlsPlaylistGenerator::HlsPlaylistGenerator() {
	// TODO Auto-generated constructor stub

}

HlsPlaylistGenerator::~HlsPlaylistGenerator() {
	// TODO Auto-generated destructor stub
}

void HlsPlaylistGenerator::test_playlist_gen(ConfigParams & config)
{
	for(auto it = config.variant_streams.begin(), ite = config.variant_streams.end(); it != ite; it++)
	{
		it->mediaUrl->publish_playlist();
		if(it->generate_iframe_url)
			it->iframeUrl->publish_playlist();
	}
}


