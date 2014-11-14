/*
 * ChunkIndex.h
 *
 *  Created on: Aug 12, 2014
 *      Author: satram
 */

#ifndef CHUNKINDEX_H_
#define CHUNKINDEX_H_

//#include "segmenterCommon.h"
#include "IndexBase.h"

class ChunkIndex : public IndexBase
{
	static unsigned int input_chunk_interval;
	bool discontinuity_flag;

public:
	ChunkIndex();
	ChunkIndex(IFrameIndex *iframe);
	virtual ~ChunkIndex();
	bool update_chunk(IFrameIndex *iframe);
	void set_interval(unsigned int interval)
	{
		input_chunk_interval = interval;
	};
	void dispatch(PlaylistInterface *playlist, VariantPlaylist *var, bool addition)
	{
		playlist->update_node(this, var, addition);
	};

	friend class MediaPlaylist;
};

#endif /* CHUNKINDEX_H_ */
