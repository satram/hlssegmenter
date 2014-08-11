/*
 * VariantPlaylist.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: satram
 */

#include "VariantPlaylist.h"

VariantPlaylist::VariantPlaylist(ConfigParams &config, variant_stream_info &var)
{
	transcoded_output_filename = "transcoded_output.ts";
	media_playlist_filename = "media.m3u8";
	iframe_playlist_filename = "iframe.m3u8";

	transcoded_output_url = config.web_server_url + "/" + var.id + "/";
	transcoded_output_path = config.output_folder + "/" + var.id + "/";

	mediaUrl = new MediaPlaylist();
	mediaUrl->add_header(var);
	mediaUrl->add_header(config);
	if(var.generate_iframe_url)
	{
		iframeUrl = new IFramePlaylist();
		iframeUrl->add_header(var);
		iframeUrl->add_header(config);
	}
}

VariantPlaylist::~VariantPlaylist()
{
	if(mediaUrl)
		delete mediaUrl;
	if(iframeUrl)
		delete iframeUrl;
}

void VariantPlaylist::publish_playlist()
{
	mediaUrl->publish_playlist();
	if(iframeUrl)
		iframeUrl->publish_playlist();
}


void VariantPlaylist::update_media_playlist(IFrameIndex *index)
{
	mediaUrl->add_node(index, this);
	mediaUrl->publish_playlist();
}

void VariantPlaylist::update_iframe_playlist(IFrameIndex *index)
{
	iframeUrl->add_node(index, this);
	iframeUrl->publish_playlist();
}




