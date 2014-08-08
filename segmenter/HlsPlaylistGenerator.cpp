	/*
 * HlsPlaylistGenerator.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "HlsPlaylistGenerator.h"

HlsPlaylistGenerator::HlsPlaylistGenerator() {
	master = new MasterPlaylist();
}

HlsPlaylistGenerator::~HlsPlaylistGenerator() {
	// TODO Auto-generated destructor stub
}

void HlsPlaylistGenerator::generate_header(ConfigParams & config)
{
	master->add_header(config);
	master->publish_playlist();
	for(auto it = config.variant_streams.begin(), ite = config.variant_streams.end(); it != ite; it++)
	{
		it->mediaUrl = new MediaPlaylist();
		it->mediaUrl->add_header(*it);
		it->mediaUrl->add_header(config);
		it->mediaUrl->publish_playlist();
		if(it->generate_iframe_url)
		{
			it->iframeUrl = new IFramePlaylist();
			it->iframeUrl->add_header(*it);
			it->iframeUrl->add_header(config);
			it->iframeUrl->publish_playlist();
		}
	}
}

void HlsPlaylistGenerator::update_header()
{
}




