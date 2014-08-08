/*
 * Segmenter.h
 *
 *  Created on: Aug 7, 2014
 *      Author: satram
 */

#ifndef SEGMENTER_H_
#define SEGMENTER_H_

#include "segmenterCommon.h"

class idr_info
{
	int total_pkt_count;
	long long pts;
	long long total_byte_offset;
	double duration_from_last_idr;
	bool chunk_start;
public:
	idr_info(int count, long long timestamp, long long byte_offset): total_pkt_count(count), pts(timestamp), total_byte_offset(byte_offset){};
	~idr_info(){};
};


class Segmenter {

	std::list<idr_info *> index;
	int ts_packet_count;
	long long byte_offset;

	ParseTsStream input_ts_stream;
	HlsPlaylistGenerator* hls_playlist;

public:
	Segmenter(ConfigParams &config);
	virtual ~Segmenter();

	void parse_ts_packets(const char *inp_buffer, int bufsize);
};

#endif /* SEGMENTER_H_ */
