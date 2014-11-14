/*
 * TsPacket.h
 *
 *  Created on: Jul 16, 2014
 *      Author: satram
 */

#ifndef TSPACKET_H_
#define TSPACKET_H_

#include "mt_common.h"

class TsPacket {
	log4c_category_t *mycat;
	int count;

	int data_packet_start_byte_offset;
	int ts_packet_size;

	int adaptation_field_control;
	bool payload_unit_start_indicator;
	int pid;
	ParseTsHeader *tsheader;
	ParsePESPacket *pes_packet;
	ParseAdaptationField *adaptation_header;

public:
//	static Profiler *level1_timer;
//	static Profiler *level2_timer;
//	static Profiler *level3_timer;

	TsPacket(int ts_packet_count);
	virtual ~TsPacket();
	void input_bitstream(Bitstream &bitstream);
    int get_pid();
    void parse_data_byte(Bitstream & bitstream, bool parse_data);
    void skip_to_end(Bitstream &bitstream);
    int get_count();
    bool get_PUSI_flag();
    long long get_PTS();
    long long get_DTS();
    int get_start_offset();
    ParsePESPacket *get_pes_packet();
};

#endif /* TSPACKET_H_ */
