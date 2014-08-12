/*
 * IFrameIndex.h
 *
 *  Created on: Aug 8, 2014
 *      Author: satram
 */

#ifndef IFRAMEINDEX_H_
#define IFRAMEINDEX_H_

#include "segmenterCommon.h"


class decision_flags
{
	bool idr_size_calculated;
	std::pair<bool,bool> update_iframe_playlist; //pair of do and done
	std::pair<bool,bool> update_media_playlist; //pair of do and done
public:
	decision_flags()
	{
		idr_size_calculated = false;
		update_iframe_playlist = std::pair<bool,bool>(false, false);
		update_media_playlist = std::pair<bool,bool>(false, false);
	}
	~decision_flags() {};
	friend class IFrameIndex;
	friend class Segmenter;
};


class IFrameIndex {

	int total_pkt_count;
	long long idr_start_offset;
	int duration;

	long long idr_size;
	unsigned int idr_duration;

	long long chunk_start_offset;
	long long chunk_size;
	unsigned int chunk_duration;

	decision_flags flags;
public:
	IFrameIndex(int count, int duration_ms, long long byte_offset, IFrameIndex *prev);
	virtual ~IFrameIndex();
	void update(int count, int duration_ms, long long byte_offset);
	void finalize(int count, int duration_ms, long long byte_offset);
	void start_chunk();
	void finalize_chunk();
	friend class Segmenter;
	friend class MediaPlaylist;
	friend class IFramePlaylist;
};

#endif /* IFRAMEINDEX_H_ */
