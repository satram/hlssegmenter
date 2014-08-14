/*
 * ChunkIndex.cpp
 *
 *  Created on: Aug 12, 2014
 *      Author: satram
 */

#include "ChunkIndex.h"

unsigned int ChunkIndex::input_chunk_interval = 0;

ChunkIndex::ChunkIndex() {
	add_to_playlist = std::pair<bool,bool>(false, false);
	chunk_start_offset = 0;
	chunk_size = 0;
	chunk_duration = 0;
}

ChunkIndex::ChunkIndex(IFrameIndex *iframe) {
	add_to_playlist = std::pair<bool,bool>(false, false);
	chunk_start_offset = iframe->idr_start_offset;
	chunk_size = 0;
	chunk_duration = iframe->accum_gop_duration;
}

ChunkIndex::~ChunkIndex() {
	// TODO Auto-generated destructor stub
}

bool ChunkIndex::update_chunk(IFrameIndex *iframe)
{
	if(chunk_duration + iframe->accum_gop_duration > input_chunk_interval)
	{
		chunk_size = iframe->idr_start_offset - chunk_start_offset;
		add_to_playlist.first = true;
		return true;
	}
	else
	{
		if (chunk_start_offset == 0)
			chunk_start_offset = iframe->idr_start_offset;
		chunk_size = iframe->idr_start_offset - chunk_start_offset; //TODO chunk size is also summation of accum_gop_size in all IDRs
		chunk_duration += iframe->accum_gop_duration;
		return false;
	}
}




