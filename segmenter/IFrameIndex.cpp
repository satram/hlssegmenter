/*
 * IFrameIndex.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: satram
 */

#include "IFrameIndex.h"

IFrameIndex::IFrameIndex(int count, long long timestamp, long long byte_offset)
{
	total_pkt_count = count;
	dts = timestamp;
	total_byte_offset = byte_offset;
	flags.idr_identified = true;
	idr_size = 0;
	chunk_size = 0;
	duration_from_last_idr = 0;
}

IFrameIndex::~IFrameIndex() {

}

void IFrameIndex::update(int count, long long timestamp, long long byte_offset)
{
	if(flags.idr_identified)
	{
		if(!flags.idr_size_calculated)
		{
			idr_size = byte_offset - total_byte_offset;
			flags.idr_size_calculated = true;
		}
		duration_from_last_idr += timestamp;
	}
}

void IFrameIndex::finalize(int count, long long timestamp, long long byte_offset)
{
	if(flags.idr_identified)
	{
		duration_from_last_idr += timestamp;
		flags.update_iframe_playlist = true;
	}
}
