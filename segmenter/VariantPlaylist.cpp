/*
 * VariantPlaylist.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: satram
 */

#include "VariantPlaylist.h"
#include "MediaPlaylist.h"
#include "IFramePlaylist.h"
#include "IndexBase.h"

VariantPlaylist::VariantPlaylist(HlsConfigParams &config, variant_stream_info &var)
{
	transcoded_output_filename = "transcoded_output.ts";
	media_playlist_filename = "media.m3u8";
	iframe_playlist_filename = "iframe.m3u8";
	ready_for_streaming_filename = "ready_for_streaming";
	leaf_id = config.leaf_id;

	std::ostringstream oss;
	oss << config.web_server_url;
	if(!config.web_server_url.empty() && config.web_server_url.find_last_of("/") != (config.web_server_url.size()-1))
		oss << "/";
	oss << var.id << "/"; //not needed for relative paths
	//transcoded_output_url = oss.str();
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

void VariantPlaylist::add_header(HlsConfigParams & config, variant_stream_info & var)
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
	index->dispatch(mediaUrl, this, addition);
	index->dispatch(iframeUrl, this, addition);
}


void VariantPlaylist::publish_media(const char *inp_buffer, int bufsize)
{
//	std::cout << "publish_media called for " << transcoded_output_path + transcoded_output_filename << std::endl;
	if(mediafile.is_open())
	{
		mediafile.write(inp_buffer, bufsize);
		mediafile.flush();
	}
//	else
//		std::cout << "output file is not open " << transcoded_output_path + transcoded_output_filename << std::endl;
}

