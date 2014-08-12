/*
 * IFrameIndex.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: satram
 */

#include "IFrameIndex.h"

IFrameIndex::IFrameIndex(int count, long long timestamp, long long byte_offset, IFrameIndex *prev)
{
	//current entry
	total_pkt_count = count;
	dts = timestamp;
	idr_start_offset = byte_offset;

	//needed for finalize idr entries
	idr_size = 0;
	idr_duration = dts;

	//needed for chunk decision
	chunk_start_offset = 0;
	chunk_size = 0;
	chunk_duration = 0;
	if(prev != 0)
	{
		chunk_start_offset = prev->chunk_start_offset;
		chunk_duration = prev->chunk_duration;
		chunk_size = prev->chunk_size;
	}
}

IFrameIndex::~IFrameIndex()
{

}

void IFrameIndex::update(int count, long long timestamp, long long byte_offset)
{
	if(!flags.idr_size_calculated)
	{
		idr_size = byte_offset - idr_start_offset;
		flags.idr_size_calculated = true;
	}
	idr_duration += timestamp;
	chunk_duration += timestamp;
	chunk_size = byte_offset - chunk_start_offset;
}

void IFrameIndex::finalize(int count, long long timestamp, long long byte_offset)
{
	idr_duration += timestamp;
	flags.update_iframe_playlist.first = true;
	chunk_duration += timestamp;
	chunk_size = byte_offset - chunk_start_offset;
}

void IFrameIndex::start_chunk()
{
	//needed for chunk decision
	chunk_start_offset = idr_start_offset;
	chunk_size = 0;
	chunk_duration = idr_duration;
}
void IFrameIndex::finalize_chunk()
{
	flags.update_media_playlist.first = true;
}
