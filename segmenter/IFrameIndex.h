/*
 * IFrameIndex.h
 *
 *  Created on: Aug 8, 2014
 *      Author: satram
 */

#ifndef IFRAMEINDEX_H_
#define IFRAMEINDEX_H_

#include "segmenterCommon.h"


class IFrameIndex {

	int total_pkt_count;

	long long idr_start_offset;
	long long idr_size;

	unsigned int accum_gop_duration;
	long long accum_gop_size;

	long long prev_packet_byte_offset;

	bool idr_size_calculated;
	std::pair<bool,bool> update_iframe_playlist; //pair of do and done

public:
	IFrameIndex(int count, int duration_ms, long long byte_offset);
	virtual ~IFrameIndex();
	void update(int count, int duration_ms, long long byte_offset);
	void finalize(int count, int duration_ms, long long byte_offset);
	friend class Segmenter;
	friend class IFramePlaylist;
	friend class ChunkIndex;
};

#endif /* IFRAMEINDEX_H_ */
