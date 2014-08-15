/*
 * VariantPlaylist.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: satram
 */

#include "VariantPlaylist.h"
#include "MediaPlaylist.h"
#include "IFramePlaylist.h"

VariantPlaylist::VariantPlaylist(ConfigParams &config, variant_stream_info &var)
{
	transcoded_output_filename = "transcoded_output.ts";
	media_playlist_filename = "media.m3u8";
	iframe_playlist_filename = "iframe.m3u8";

	transcoded_output_url = config.web_server_url + "/" + var.id + "/";
	transcoded_output_path = config.output_folder + "/" + var.id + "/";

	mediaUrl = new MediaPlaylist();
	mediaUrl->set_url(transcoded_output_path, media_playlist_filename);
    if(var.generate_iframe_url)
    {
        iframeUrl = new IFramePlaylist();
        iframeUrl->set_url(transcoded_output_path, iframe_playlist_filename);
    }

    mediafile.open(transcoded_output_path + transcoded_output_filename, std::ofstream::out);
}

VariantPlaylist::~VariantPlaylist()
{
	if(mediaUrl)
		delete mediaUrl;
	if(iframeUrl)
		delete iframeUrl;
	if(mediafile.is_open())
		mediafile.close();
}

void VariantPlaylist::add_header(ConfigParams & config, variant_stream_info & var)
{
    mediaUrl->add_header(var);
    mediaUrl->add_header(config);
    if(iframeUrl){
        iframeUrl->add_header(var);
        iframeUrl->add_header(config);
    }
}


void VariantPlaylist::publish_playlist()
{
	mediaUrl->publish_playlist();
	if(iframeUrl)
		iframeUrl->publish_playlist();
}

void VariantPlaylist::finalize_playlist()
{
	mediaUrl->finalize_playlist();
	if(iframeUrl)
		iframeUrl->finalize_playlist();
}

void VariantPlaylist::update_playlist(IndexBase *index, bool addition)
{
	if(dynamic_cast<ChunkIndex *>(index))
	{
		mediaUrl->update_node(index, this, addition);
	}
	else
	{
		iframeUrl->update_node(index, this, addition);
	}
}


void VariantPlaylist::publish_media(const char *inp_buffer, int bufsize)
{
	if(mediafile.is_open())
	{
		mediafile.write(inp_buffer, bufsize);
	}
}

