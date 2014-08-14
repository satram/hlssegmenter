/*
 * MediaPlaylist.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "MediaPlaylist.h"

MediaPlaylist::MediaPlaylist() {
	// TODO Auto-generated constructor stub

}

MediaPlaylist::~MediaPlaylist() {
	// TODO Auto-generated destructor stub
}


void MediaPlaylist::add_header(variant_stream_info &stream_info)
{
	Section header("header");
	header.add_tag("M3U");
	header.add_tag("VERSION", 4);
	header.add_tag("MEDIA-SEQUENCE", 0);
	playlist.add_section(header);
}

void MediaPlaylist::add_node(IndexBase *idx, VariantPlaylist *variant_playlist)
{
	ChunkIndex *index = dynamic_cast<ChunkIndex *> (idx);
	std::ostringstream oss;
	oss << "node-" << index->chunk_duration;
	Section node(oss.str());
	double duration = (double)index->chunk_duration / 1000.0;
	//std::cout << "chunk duration " << duration << std::endl;
	node.add_tag("INF", duration);
	oss.str("");
	oss << index->chunk_size << "@" << index->chunk_start_offset;
	node.add_tag("BYTERANGE", oss.str());
	node.set_path(variant_playlist->transcoded_output_url);
	node.set_locator(variant_playlist->transcoded_output_filename);
	playlist.add_section(node);
}

void MediaPlaylist::remove_node(IndexBase *idx)
{
	ChunkIndex *index = dynamic_cast<ChunkIndex *> (idx);
	std::ostringstream oss;
	oss << "node-" << index->chunk_duration;
	playlist.delete_section(oss.str());
}

void MediaPlaylist::add_header(ConfigParams & config)
{
	Section header = playlist.get_section("header");
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
