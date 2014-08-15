/*
 * ChunkIndex.h
 *
 *  Created on: Aug 12, 2014
 *      Author: satram
 */

#ifndef CHUNKINDEX_H_
#define CHUNKINDEX_H_

#include "segmenterCommon.h"

class ChunkIndex : public IndexBase
{
	static unsigned int input_chunk_interval;

public:
	ChunkIndex();
	ChunkIndex(IFrameIndex *iframe);
	virtual ~ChunkIndex();
	bool update_chunk(IFrameIndex *iframe);
	void set_interval(unsigned int interval)
	{
		input_chunk_interval = interval;
	};


	friend class Segmenter;
};

#endif /* CHUNKINDEX_H_ */
