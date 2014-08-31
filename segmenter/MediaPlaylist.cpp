/*
 * MediaPlaylist.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "MediaPlaylist.h"
#include "ChunkIndex.h"
#include "VariantPlaylist.h"

MediaPlaylist::MediaPlaylist() {
	sequence_number = 0;
	node_count = 0;
}

MediaPlaylist::~MediaPlaylist() {
	// TODO Auto-generated destructor stub
}


void MediaPlaylist::add_header(variant_stream_info &stream_info)
{
	Section header("header");
	header.add_tag("M3U");
	header.add_tag("VERSION", 4);
	header.add_tag("MEDIA-SEQUENCE", sequence_number);
	playlist.add_section(header);
}

void MediaPlaylist::update_node(ChunkIndex *index, VariantPlaylist *variant_playlist, bool addition)
{
	std::ostringstream oss;
	oss << "node-" << index->duration;
	if(addition)
	{
		Section node(oss.str());
		double duration = (double)index->duration / 1000.0;
		//std::cout << "chunk duration " << duration << std::endl;
		node.add_tag("INF", duration);
		oss.str("");
		oss << index->size << "@" << index->start_offset;
		node.add_tag("BYTERANGE", oss.str());
		node.set_path(variant_playlist->transcoded_output_url);
		//		oss.str("");
		//		oss << "file-" << node_count++;
		//		node.set_locator(oss.str());
		node.set_locator(variant_playlist->transcoded_output_filename);
		playlist.add_section(node);
		node_count++;
	}
	else
	{
		playlist.delete_section(oss.str());
		sequence_number++;
		Section header = playlist.get_section("header");
		header.modify_tag("MEDIA-SEQUENCE", sequence_number);
		playlist.modify_section(header);
	}
}

void MediaPlaylist::add_header(ConfigParams & config)
{
	Section header = playlist.get_section("header");
	if(config.playlist_type != LIVE)
		header.add_tag("PLAYLIST-TYPE", config.convert_playlist_enum_to_string(config.playlist_type));
	double duration = (double)config.segment_duration_ms / 1000.0;
	header.add_tag("TARGETDURATION", duration);
	playlist.modify_section(header);
}

void MediaPlaylist::add_footer()
{
	Section footer ("footer");
	footer.add_tag("ENDLIST");
	playlist.add_section(footer);
}

void MediaPlaylist::finalize_playlist()
{
	Section header = playlist.get_section("header");
	header.modify_tag("PLAYLIST-TYPE", "VOD");
	playlist.modify_section(header);
	add_footer();
}
