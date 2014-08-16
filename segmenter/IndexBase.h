/*
 * IndexBase.h
 *
 *  Created on: Aug 13, 2014
 *      Author: satram
 */

#ifndef INDEXBASE_H_
#define INDEXBASE_H_

#include <utility>
#include "PlaylistInterface.h"

class IndexBase
{
	std::pair<bool,bool> add_to_playlist; //pair of do and done
	unsigned int duration;
	long long start_offset;
	long long size;
	bool purge;

public:
	IndexBase();
	virtual ~IndexBase();
	virtual void dispatch(PlaylistInterface *playlist, VariantPlaylist *var, bool addition)
	{
		throw std::runtime_error("not implemented in base class");
	};

	friend class Segmenter;
	friend class ChunkIndex;
	friend class IFrameIndex;
	friend class IFramePlaylist;
	friend class MediaPlaylist;
};



#endif /* INDEXBASE_H_ */
