/*
 * Segmenter.h
 *
 *  Created on: Aug 7, 2014
 *      Author: satram
 */

#ifndef SEGMENTER_H_
#define SEGMENTER_H_

#include "segmenterCommon.h"

struct idr_info
{
	int pkt_counter;
	long long pts;
	double duration_from_last_idr;
	bool chunk_start;
	idr_info(int count, long long timestamp): pkt_counter(count), pts(timestamp){};
	virtual ~idr_info();
};


class Segmenter {

	std::list<idr_info> index;
	int ts_packet_count;

	ParseTsStream input_ts_stream;
	HlsPlaylistGenerator* hls_playlist;

public:
	Segmenter(ConfigParams &config);
	virtual ~Segmenter();

	void parse_ts_packets(const char *inp_buffer, int bufsize);
};

#endif /* SEGMENTER_H_ */
