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

HlsPlaylistGenerator::~HlsPlaylistGenerator()
{
}

void HlsPlaylistGenerator::generate_header(ConfigParams & config)
{
	master->add_header(config);
	master->publish_playlist();
	for(auto it = config.variant_streams.begin(), ite = config.variant_streams.end(); it != ite; it++)
	{
		//set the names based on global config
		it->transcoded_output_url = config.web_server_url + "/" + it->id + "/";
		it->transcoded_output_path = config.output_folder + "/" + it->id + "/";
		it->transcoded_output_filename = "transcoded_output.ts"; //TODO change to acceptable name
		it->media_playlist_filename = "media.m3u8";		//TODO change to acceptable name
		it->iframe_playlist_filename = "iframe.m3u8";	//TODO change to acceptable name

		//allocate media playlist memory
		it->mediaUrl = new MediaPlaylist();
		it->mediaUrl->add_header(*it);
		it->mediaUrl->add_header(config);
		it->mediaUrl->publish_playlist(); //TODO - only for testing, this call happens somewhere else
		if(it->generate_iframe_url)
		{
			//allocate iframe playlist memory
			it->iframeUrl = new IFramePlaylist();
			it->iframeUrl->add_header(*it);
			it->iframeUrl->add_header(config);
			it->iframeUrl->publish_playlist(); //TODO - only for testing, this call happens somewhere else
		}
	}
}

void HlsPlaylistGenerator::update_header()
{
}




