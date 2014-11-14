	/*
 * HlsPlaylistGenerator.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "HlsPlaylistGenerator.h"
#include "MasterPlaylist.h"
#include "VariantPlaylist.h"

HlsPlaylistGenerator::HlsPlaylistGenerator(HlsConfigParams &config)
{
	master = new MasterPlaylist();
	std::string master_playlistname = "master.m3u8";
	master->set_url(config.output_folder, master_playlistname);
	for(auto it = config.variant_streams.begin(), ite = config.variant_streams.end(); it != ite; it++)
	{
		VariantPlaylist *var = new VariantPlaylist(config, *it);
		variants.push_back(var);
	}
}

HlsPlaylistGenerator::~HlsPlaylistGenerator()
{
	if(master)
		delete master;
	for(auto it = variants.begin(), ite = variants.end(); it != ite; it++)
		delete (*it);
}

void HlsPlaylistGenerator::generate_header(HlsConfigParams & config)
{
	master->add_header(config);
	auto var_stream_info = config.variant_streams.begin();
	for(auto it = variants.begin(), ite = variants.end(); it != ite; it++, var_stream_info++)
	{
		(*it)->add_header(config, *var_stream_info);
	}
}

void HlsPlaylistGenerator::update(IndexBase *index, bool addition)
{
	VariantPlaylist * it = variants.back();
	it->update_playlist(index, addition);
}

void HlsPlaylistGenerator::publish_playlist()
{
	master->publish_playlist();
	for(auto it = variants.begin(), ite = variants.end(); it != ite; it++)
	{
		(*it)->publish_playlist();
	}
}

void HlsPlaylistGenerator::publish_media(const char *inp_buffer, int bufsize)
{
//	std::cout << "publish_media called\n";
	VariantPlaylist * it = variants.back();
	it->publish_media(inp_buffer, bufsize);
}

void HlsPlaylistGenerator::finalize_playlist()
{
	master->finalize_playlist();
	for(auto it = variants.begin(), ite = variants.end(); it != ite; it++)
	{
		(*it)->finalize_playlist();
	}
}
