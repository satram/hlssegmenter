/*
 * IFrameIndex.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: satram
 */

#include "IFrameIndex.h"

IFrameIndex::IFrameIndex(int count, long long byte_offset)
{
	//current entry
	total_pkt_count = count;
	start_offset = byte_offset;

	//needed for finalize idr entries
	size = 0;
	add_to_playlist = std::pair<bool,bool>(false, false);

	duration = 0;
	accum_gop_size = 0;
	prev_packet_byte_offset = byte_offset;
	purge = false;
}

IFrameIndex::~IFrameIndex()
{

}

void IFrameIndex::update(int count,long long byte_offset)
{
	if(size == 0)
		size = byte_offset - start_offset;

	accum_gop_size += byte_offset - prev_packet_byte_offset;
	prev_packet_byte_offset = byte_offset;
}

void IFrameIndex::finalize(int count, int duration_ms, long long byte_offset)
{
	add_to_playlist.first = true;
	duration = duration_ms;
	accum_gop_size += byte_offset - prev_packet_byte_offset;
	prev_packet_byte_offset = byte_offset;
}

