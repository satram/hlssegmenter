/*
 * IFramePlaylist.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "IFramePlaylist.h"
#include "IFrameIndex.h"
#include "VariantPlaylist.h"

IFramePlaylist::IFramePlaylist() {
	// TODO Auto-generated constructor stub

}

IFramePlaylist::~IFramePlaylist() {
	// TODO Auto-generated destructor stub
}


void IFramePlaylist::add_header(HlsConfigParams & config)
{
    Section header = playlist.get_section("header");
    if(config.playlist_type != LIVE)
    header.add_tag("PLAYLIST-TYPE", config.convert_playlist_enum_to_string(config.playlist_type));
    double duration = (double)config.segment_duration_ms / 1000.0;
    header.add_tag("TARGETDURATION", duration);
    playlist.modify_section(header);
}

void IFramePlaylist::update_node(IFrameIndex *index, VariantPlaylist *variant_playlist, bool addition)
{
	std::ostringstream oss;
	oss << "node-" << index->duration;
	if(addition)
	{
		Section node(oss.str());
		double duration = (double)index->duration / 1000.0;
		node.add_tag("INF", duration);
		oss.str("");
		oss << index->size << "@" << index->start_offset;
		node.add_tag("BYTERANGE", oss.str());
		node.set_path(variant_playlist->transcoded_output_url);
		node.set_locator(variant_playlist->transcoded_output_filename);
		playlist.add_section(node);
	}
	else
		playlist.delete_section(oss.str());
}



void IFramePlaylist::add_header(variant_stream_info &stream_info)
{
	Section header("header");
	header.add_tag("M3U");
	header.add_tag("VERSION", 4);
	header.add_tag("I-FRAMES-ONLY");
	playlist.add_section(header);
}

void IFramePlaylist::add_footer()
{
	Section footer ("footer");
	footer.add_tag("ENDLIST");
	playlist.add_section(footer);
}

void IFramePlaylist::finalize_playlist()
{
	add_footer();
}


