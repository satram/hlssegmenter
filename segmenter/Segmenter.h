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

	ParseTsStream input_ts_stream;
	HlsPlaylistGenerator* hls_playlist;

public:
	Segmenter(ConfigParams &config);
	virtual ~Segmenter();

	void parse_ts_packets(const char *inp_buffer, int bufsize);
};

#endif /* SEGMENTER_H_ */
