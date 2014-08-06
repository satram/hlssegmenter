/*
 * ConfigParams.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "ConfigParams.h"

ConfigParams::ConfigParams() {
	num_variant_streams = 0;
}

ConfigParams::~ConfigParams() {
	// TODO Auto-generated destructor stub
}

void ConfigParams::add_variant(variant_stream_info & var)
{
	num_variant_streams++;
	var.mediaUrl = new MediaPlaylist();
	if(var.generate_iframe_url)
		var.iframeUrl = new IFramePlaylist();
	variant_streams.push_back(var);
}

void ConfigParams::remove_variant(std::string id)
{
	for(auto it = variant_streams.begin(), ite = variant_streams.end(); it != ite; it++)
	{
		if(it->id == id)
		{
			variant_streams.erase(it);
			delete (it->mediaUrl);
			delete (it->iframeUrl);
			break;
		}
	}
}




