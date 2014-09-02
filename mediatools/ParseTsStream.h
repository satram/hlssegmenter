/*
 * ParseTsStream.h
 *
 *  Created on: Jul 2, 2014
 *      Author: satram
 */

#ifndef PARSETSSTREAM_H_
#define PARSETSSTREAM_H_

#include "mt_common.h"
#include "Bitstream.h"
#include "Profiler.h"
#include "ElementaryStream.h"
#include "VideoStream.h"

class ParseTsStream {

	log4c_category_t* mycat;
	std::map<int, int> pid_list;


	Bitstream bitstream;
	std::vector <TsPacket *> ts_pkt_list;

    int pmt_pid;
    int video_pid;
    int audio_pid;
    PatParse *pat_packet;
    PmtParse *pmt_packet;
    VideoStream *video_stream;
    AudioStream *audio_stream;

    Profiler input_memcopy;
    Profiler pes_pkt_copy;
    Profiler ts_pkt_profiler;
    Profiler video_pkt_profiler;
    Profiler audio_pkt_profiler;

    int ts_packet_count;

    void update_pid_list(int & pid);

public:
	ParseTsStream();
	virtual ~ParseTsStream();
	void print_pid_list();
	void print_stats();
	int get_num_packets();
    void open(std::string & inpFile);
    void open(std::streambuf *rdbuf);
    void open(const char *buf, int length);
    void close();
    void parse_bytestream();
    std::list<VideoPktInfo *> &get_pkt_info();
};

#endif /* PARSETSSTREAM_H_ */
