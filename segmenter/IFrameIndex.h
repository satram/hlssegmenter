/*
 * IFrameIndex.h
 *
 *  Created on: Aug 8, 2014
 *      Author: satram
 */

#ifndef IFRAMEINDEX_H_
#define IFRAMEINDEX_H_

//#include "segmenterCommon.h"
#include "IndexBase.h"

class IFrameIndex : public IndexBase {

	int total_pkt_count;
	long long accum_gop_size;
	long long prev_packet_byte_offset;


public:
	IFrameIndex(int count, long long byte_offset);
	virtual ~IFrameIndex();
	void update(int count, long long byte_offset);
	void finalize(int count, int duration_ms, long long byte_offset);
	void dispatch(PlaylistInterface *playlist, VariantPlaylist *var, bool addition)
	{
		playlist->update_node(this, var, addition);
	};
	friend class IFramePlaylist;
	friend class ChunkIndex;
};

#endif /* IFRAMEINDEX_H_ */
