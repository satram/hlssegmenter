/*
 * IFramePlaylist.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "IFramePlaylist.h"

IFramePlaylist::IFramePlaylist() {
	// TODO Auto-generated constructor stub

}

IFramePlaylist::~IFramePlaylist() {
	// TODO Auto-generated destructor stub
}


void IFramePlaylist::add_header(ConfigParams & config)
{
}

void IFramePlaylist::add_node(IndexBase *idx, VariantPlaylist *variant_playlist)
{
	IFrameIndex *index = dynamic_cast<IFrameIndex *>(idx);
	std::ostringstream oss;
	oss << "node-" << index->total_pkt_count;
	Section node(oss.str());
	double duration = (double)index->accum_gop_duration / 1000.0;
	//std::cout << "IDR duration " << duration << std::endl;
	node.add_tag("INF", duration);
	oss.str("");
	oss << index->idr_size << "@" << index->idr_start_offset;
	node.add_tag("BYTERANGE", oss.str());
	node.set_path(variant_playlist->transcoded_output_url);
	node.set_locator(variant_playlist->transcoded_output_filename);
	playlist.add_section(node);
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

void IFramePlaylist::remove_node(IndexBase *idx)
{
	IFrameIndex *index = dynamic_cast<IFrameIndex *>(idx);
	std::ostringstream oss;
	oss << "node-" << index->total_pkt_count;
	playlist.delete_section(oss.str());

}

void IFramePlaylist::finalize_playlist()
{
	add_footer();
}


