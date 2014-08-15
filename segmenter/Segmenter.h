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

	std::list<IndexBase *> iframe_index;
	std::list<IndexBase *> chunk_index;
	ChunkIndex *curr_chunk;

	int ts_packet_count;
	long long byte_offset;

	ParseTsStream input_ts_stream;

	HlsPlaylistGenerator* hls_playlist;

	void update_iframe_index();
    void update_playlists();
    void update_chunk_index(IFrameIndex *last_iframe);
    void check_index_add(std::list<IndexBase *> &index);
    void check_index_remove(std::list<IndexBase *> &index);

    unsigned int segment_duration;
    unsigned int sliding_window_duration;
    hls_playlist_type playlist_type;

    bool update_playlist;
    long long prev_timestamp;

public:
	Segmenter(ConfigParams &config);
	virtual ~Segmenter();

	void parse_ts_packets(const char *inp_buffer, int bufsize);
	void finalize_playlist();
};

#endif /* SEGMENTER_H_ */
