	/*
 * HlsPlaylistGenerator.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "HlsPlaylistGenerator.h"

HlsPlaylistGenerator::HlsPlaylistGenerator()
{
	master = new MasterPlaylist();
}

HlsPlaylistGenerator::~HlsPlaylistGenerator()
{
	if(master)
		delete master;

}

void HlsPlaylistGenerator::generate_header(ConfigParams & config)
{
	master->add_header(config);
	master->publish_playlist();
	for(auto it = config.variant_streams.begin(), ite = config.variant_streams.end(); it != ite; it++)
	{
		VariantPlaylist *var = new VariantPlaylist(config, *it);
		variants.push_back(var);
		var->publish_playlist();
	}
}

void HlsPlaylistGenerator::update_media(IFrameIndex *index)
{
	//TODO make this call go to corresponding variant
	VariantPlaylist * it = variants.back();
	it->update_media_playlist(index);
}

void HlsPlaylistGenerator::update_iframe(IFrameIndex *index)
{
	//TODO make this call go to corresponding variant
	VariantPlaylist * it = variants.back();
	it->update_iframe_playlist(index);
}



