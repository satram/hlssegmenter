/*
 * ParsePESPacket.h
 *
 *  Created on: Jul 7, 2014
 *      Author: satram
 */

#ifndef PARSEPESPACKET_H_
#define PARSEPESPACKET_H_

#include "Common.h"

class ParsePESPacket {

	enum stream_id_enum{
		program_stream_map = 0xbc,
		private_stream_1 = 0xbd,
		padding_stream = 0xbe,
		private_stream_2 = 0xbf,

		ECM_stream = 0xf0,
		EMM_stream = 0xf1,
		DSMCC_stream = 0xf2,
		IEC_13522_stream = 0xf3,
		H222_1_type_A = 0xf4,
		H222_1_type_B = 0xf5,
		H222_1_type_C = 0xf6,
		H222_1_type_D = 0xf7,
		H222_1_type_E = 0xf8,
		ancillary_stream = 0xf9,
		SL_packetized_stream = 0xfa,
		FlexMux_stream = 0xfb,

		program_stream_directory = 0xff
	};

	enum TrickModeControl{
		fast_forward,
		slow_motion,
		freeze_frame,
		fast_reverse,
		slow_reverse
	};

	int packet_start_code_prefix;
	int stream_id;
	int PES_packet_length;

	int PES_scrambling_control;
	bool PES_priority;
	bool data_alignment_indicator;
	bool copyright;
	bool original_or_copy;
	int PTS_DTS_flags;
	bool ESCR_flag;
	bool ES_rate_flag;
	bool DSM_trick_mode_flag;
	bool additional_copy_info_flag;
	bool PES_CRC_flag;
	bool PES_extension_flag;
	int PES_header_data_length;

	long long PTS;
	long long DTS;
	long long ESCR_base;
	int ESCR_extension;
	int ES_rate;

	char trick_mode_control;

	int field_id;
	int intra_slice_refresh;
	int frequency_truncation;
	int rep_cntrl;

	int additional_copy_info;
	int previous_PES_packet_CRC;

	bool PES_private_data_flag;
	bool pack_header_field_flag;
	bool program_packet_sequence_counter_flag;
	bool PSTD_buffer_flag;
	bool PES_extension_flag_2;

	std::vector<int> PES_private_data;
	int pack_field_length;

	int program_packet_sequence_counter;
	bool MPEG1_MPEG2_identifier;
	int original_stuff_length;

	int PSTD_buffer_scale;
	int PSTD_buffer_size;

	int PES_extension_field_length;
	std::vector<char> stuffing_byte;
	std::vector<unsigned char> PES_packet_data_byte;
	std::vector<char> padding_byte;

	int pes_header_start_offset;
	int pes_data_start_offset;

	log4c_category_t* mycat;

public:
	ParsePESPacket();
	virtual ~ParsePESPacket();

	long long get_PTS();
	long long get_DTS();
    void input_bitstream(Bitstream & bitstream);
    std::vector<unsigned char>& get_data_bytes();

};

#endif /* PARSEPESPACKET_H_ */
