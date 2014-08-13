/*
 * Segmenter.h
 *
 *  Created on: Aug 7, 2014
 *      Author: satram
 */

#ifndef SEGMENTER_H_
#define SEGMENTER_H_

#include "segmenterCommon.h"


class Segmenter {

	std::vector<IFrameIndex *> iframe_index;
	std::vector<ChunkIndex *> chunk_index;
	ChunkIndex *curr_chunk;

	int ts_packet_count;
	long long byte_offset;

	ParseTsStream input_ts_stream;

	HlsPlaylistGenerator* hls_playlist;

	void create_index_table();
    void update_playlists();
    void update_chunk(IFrameIndex *last_iframe);

    double segment_duration;
    long long prev_timestamp;

public:
	Segmenter(ConfigParams &config);
	virtual ~Segmenter();

	void parse_ts_packets(const char *inp_buffer, int bufsize);
	void finalize_playlist();
};

#endif /* SEGMENTER_H_ */
