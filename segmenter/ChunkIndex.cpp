/*
 * ChunkIndex.cpp
 *
 *  Created on: Aug 12, 2014
 *      Author: satram
 */

#include "ChunkIndex.h"
#include "IFrameIndex.h"

unsigned int ChunkIndex::input_chunk_interval = 0;

ChunkIndex::ChunkIndex() {
	add_to_playlist = std::pair<bool,bool>(false, false);
	start_offset = 0;
	size = 0;
	duration = 0;
	purge = false;
}

ChunkIndex::ChunkIndex(IFrameIndex *iframe) {
	add_to_playlist = std::pair<bool,bool>(false, false);
	start_offset = iframe->start_offset;
	size = 0;
	duration = iframe->duration;
	purge = false;
}

ChunkIndex::~ChunkIndex() {
	// TODO Auto-generated destructor stub
}

bool ChunkIndex::update_chunk(IFrameIndex *iframe)
{
	if(duration + iframe->duration > input_chunk_interval)
	{
		size = iframe->start_offset - start_offset;
		add_to_playlist.first = true;
		return true;
	}
	else
	{
		if (start_offset == 0)
			start_offset = iframe->start_offset;
		size = iframe->start_offset - start_offset; //TODO chunk size is also summation of accum_gop_size in all IDRs
		duration += iframe->duration;
		return false;
	}
}


