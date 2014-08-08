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
	ts_packet_count = 0;
}

Segmenter::~Segmenter() {
	if(hls_playlist)
		delete hls_playlist;
}

void Segmenter::parse_ts_packets(const char *inp_buffer, int bufsize)
{
    input_ts_stream.open(inp_buffer, bufsize);
    input_ts_stream.parse_bytestream();

    //input_ts_stream.print_pid_list();
    //input_ts_stream.print_stats();
    std::list<VideoPktInfo *> small_list = input_ts_stream.get_pkt_info();

    hls_playlist->update_header();
    ts_packet_count += input_ts_stream.get_num_packets();
    std::cout << "ts_packet_count " << ts_packet_count << std::endl;

    input_ts_stream.close();
}


