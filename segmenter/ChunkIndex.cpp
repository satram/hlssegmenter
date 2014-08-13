/*
 * ChunkIndex.cpp
 *
 *  Created on: Aug 12, 2014
 *      Author: satram
 */

#include "ChunkIndex.h"

unsigned int ChunkIndex::input_chunk_interval = 0;

ChunkIndex::ChunkIndex() {
	update_media_playlist = std::pair<bool,bool>(false, false);
	chunk_start_offset = 0;
	chunk_size = 0;
	chunk_duration = 0;
}

ChunkIndex::ChunkIndex(IFrameIndex *iframe) {
	update_media_playlist = std::pair<bool,bool>(false, false);
	chunk_start_offset = iframe->idr_start_offset;
	chunk_size = iframe->accum_gop_size;
	chunk_duration = iframe->accum_gop_duration;
}

ChunkIndex::~ChunkIndex() {
	// TODO Auto-generated destructor stub
}

bool ChunkIndex::update_chunk(IFrameIndex *iframe)
{
	if(chunk_duration + iframe->accum_gop_duration > input_chunk_interval)
	{
		update_media_playlist.first = true;
		return true;
	}
	else
	{
		chunk_size += iframe->accum_gop_size;
		chunk_duration += iframe->accum_gop_duration;
		return false;
	}
}




