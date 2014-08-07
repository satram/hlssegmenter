/*
 * Segmenter.cpp
 *
 *  Created on: Aug 7, 2014
 *      Author: satram
 */

#include "Segmenter.h"

Segmenter::Segmenter(ConfigParams &config) {
	hls_playlist = new HlsPlaylistGenerator();
	hls_playlist->generate_header(config);
}

Segmenter::~Segmenter() {
	if(hls_playlist)
		delete hls_playlist;
}

void Segmenter::parse_ts_packets(const char *inp_buffer, int bufsize)
{
    input_ts_stream.open(inp_buffer, bufsize);
    input_ts_stream.parse_bytestream();

    input_ts_stream.print_pid_list();
    input_ts_stream.print_stats();

    hls_playlist->update_header();

    input_ts_stream.close();
}


