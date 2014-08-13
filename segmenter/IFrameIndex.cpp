/*
 * IFrameIndex.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: satram
 */

#include "IFrameIndex.h"

IFrameIndex::IFrameIndex(int count, int duration_ms, long long byte_offset)
{
	//current entry
	total_pkt_count = count;
	idr_start_offset = byte_offset;

	//needed for finalize idr entries
	idr_size = 0;
	idr_size_calculated = false;
	update_iframe_playlist = std::pair<bool,bool>(false, false);

	accum_gop_duration = duration_ms;
	accum_gop_size = 0;
	prev_packet_byte_offset = byte_offset;
}

IFrameIndex::~IFrameIndex()
{

}

void IFrameIndex::update(int count, int duration_ms, long long byte_offset)
{
	if(!idr_size_calculated)
	{
		idr_size = byte_offset - idr_start_offset;
		idr_size_calculated = true;
	}

	accum_gop_duration += duration_ms;
	accum_gop_size = byte_offset - prev_packet_byte_offset;
	prev_packet_byte_offset = byte_offset;
}

void IFrameIndex::finalize(int count, int duration_ms, long long byte_offset)
{
	update_iframe_playlist.first = true;
	accum_gop_duration += duration_ms;
	accum_gop_size = byte_offset - prev_packet_byte_offset;
	prev_packet_byte_offset = byte_offset;
}

