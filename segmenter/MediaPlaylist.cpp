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

void MediaPlaylist::add_node(IFrameIndex *index, VariantPlaylist *variant_playlist)
{
	std::ostringstream oss;
	oss << "node-" << index->total_pkt_count;
	Section node(oss.str());
	double duration = (double)index->chunk_duration / 1000.0;
	node.add_tag("INF", duration);
	oss.str("");
	oss << index->chunk_size << "@" << index->chunk_start_offset;
	node.add_tag("BYTERANGE", oss.str());
	node.set_path(variant_playlist->transcoded_output_url);
	node.set_locator(variant_playlist->transcoded_output_filename);
	playlist.add_section(node);
}

void MediaPlaylist::remove_node()
{
}

void MediaPlaylist::add_header(ConfigParams & config)
{
	Section header = playlist.get_section("header");
	if(config.playlist_type == event)
		header.add_tag("PLAYLIST-TYPE", "EVENT");
	else if(config.playlist_type == vod)
		header.add_tag("PLAYLIST-TYPE", "VOD");
	double duration = (double)config.segment_duration_ms / 1000.0;
	header.add_tag("TARGETDURATION", duration);
	playlist.modify_section(header);
}

void MediaPlaylist::add_footer()
{
}

void MediaPlaylist::finalize_playlist()
{
	Section header = playlist.get_section("header");
	header.modify_tag("PLAYLIST-TYPE", "VOD");
	playlist.modify_section(header);

	Section footer ("footer");
	footer.add_tag("ENDLIST");
	playlist.add_section(footer);
}
