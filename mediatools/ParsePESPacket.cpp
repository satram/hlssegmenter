/*
 * ParsePESPacket.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: satram
 */

#include "ParsePESPacket.h"
#include "Bitstream.h"

class PES_exception: public std::exception
{
public:
	virtual const char * what() const throw()
	{
		std::ostringstream oss;
		oss << "PES assert failure at line#" << __LINE__;
		return(oss.str().c_str());
	};
};

#define pes_assert(x) {if(!x) throw PES_exception();}


void ParsePESPacket::input_bitstream(Bitstream & bitstream)
{
	pes_header_start_offset = bitstream.get_in_byte_offset();

    packet_start_code_prefix = bitstream.read_bits(24);
    stream_id = bitstream.read_bits(8);
    PES_packet_length = bitstream.read_bits(16);
    log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "packet_start_code_prefix %x", packet_start_code_prefix);
    log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "stream_id %d", stream_id);
    log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "PES_packet_length %d", PES_packet_length);

    if(stream_id != stream_id_enum::program_stream_map
	&& stream_id != stream_id_enum::padding_stream
	&& stream_id != stream_id_enum::private_stream_2
	&& stream_id != stream_id_enum::ECM_stream
	&& stream_id != stream_id_enum::EMM_stream
	&& stream_id != stream_id_enum::program_stream_directory
	&& stream_id != stream_id_enum::DSMCC_stream
	&& stream_id != stream_id_enum::H222_1_type_E
	)
	{
		int marker = bitstream.read_bits(2);
		pes_assert(marker == 0x2);
		PES_scrambling_control = bitstream.read_bits(2);
		PES_priority = (bool)bitstream.read_bits(1);
		data_alignment_indicator = (bool)bitstream.read_bits(1);
		copyright = (bool)bitstream.read_bits(1);
		original_or_copy = (bool)bitstream.read_bits(1);
		PTS_DTS_flags = bitstream.read_bits(2);
		ESCR_flag = (bool)bitstream.read_bits(1);
		ES_rate_flag = (bool)bitstream.read_bits(1);
		DSM_trick_mode_flag = (bool)bitstream.read_bits(1);
		additional_copy_info_flag = (bool)bitstream.read_bits(1);
		PES_CRC_flag = (bool)bitstream.read_bits(1);
		PES_extension_flag = (bool)bitstream.read_bits(1);
		PES_header_data_length = bitstream.read_bits(8);

		if(PTS_DTS_flags == 0x2)
		{
			marker = bitstream.read_bits(4);
			pes_assert(marker == 0x2);
			PTS = bitstream.read_bits(3) << 30;
			bitstream.skip_bits(1);
			PTS |= (bitstream.read_bits(15) << 15);
			bitstream.skip_bits(1);
			PTS |= bitstream.read_bits(15);
			bitstream.skip_bits(1);
		}

		if(PTS_DTS_flags == 0x3)
		{
			marker = bitstream.read_bits(4);
			pes_assert(marker == 0x3);
			PTS = bitstream.read_bits(3) << 30;
			bitstream.skip_bits(1);
			PTS |= (bitstream.read_bits(15) << 15);
			bitstream.skip_bits(1);
			PTS |= bitstream.read_bits(15);
			bitstream.skip_bits(1);

			marker = bitstream.read_bits(4);
			pes_assert(marker == 0x1);
			DTS = bitstream.read_bits(3) << 30;
			bitstream.skip_bits(1);
			DTS |= (bitstream.read_bits(15) << 15);
			bitstream.skip_bits(1);
			DTS |= bitstream.read_bits(15);
			bitstream.skip_bits(1);
		}

		if(ESCR_flag)
		{
			bitstream.skip_bits(2);
			ESCR_base = bitstream.read_bits(3) << 30;
			bitstream.skip_bits(1);
			ESCR_base |= (bitstream.read_bits(15) << 15);
			bitstream.skip_bits(1);
			ESCR_base |= bitstream.read_bits(15);
			bitstream.skip_bits(1);
			ESCR_extension = bitstream.read_bits(9);
			bitstream.skip_bits(1);
		}

		if(ES_rate_flag)
		{
			bitstream.skip_bits(1);
			ES_rate = bitstream.read_bits(22);
			bitstream.skip_bits(1);
		}

		if(DSM_trick_mode_flag)
		{
			trick_mode_control = bitstream.read_bits(3);
			if(trick_mode_control == TrickModeControl::fast_forward)
			{
				field_id = bitstream.read_bits(2);
				intra_slice_refresh = bitstream.read_bits(1);
				frequency_truncation = bitstream.read_bits(2);
			}
			else if(trick_mode_control == TrickModeControl::slow_motion)
			{
				rep_cntrl = bitstream.read_bits(5);
			}
			else if(trick_mode_control == TrickModeControl::freeze_frame)
			{
				field_id = bitstream.read_bits(2);
				bitstream.skip_bits(3);
			}
			else if(trick_mode_control == TrickModeControl::fast_reverse)
			{
				field_id = bitstream.read_bits(2);
				intra_slice_refresh = bitstream.read_bits(1);
				frequency_truncation = bitstream.read_bits(2);
			}
			else if(trick_mode_control == TrickModeControl::slow_reverse)
			{
				rep_cntrl = bitstream.read_bits(5);
			}
			else
			{
				bitstream.skip_bits(5);
			}
		}

		if(additional_copy_info_flag)
		{
			bitstream.skip_bits(1);
			additional_copy_info = bitstream.read_bits(7);
		}

		if(PES_CRC_flag)
		{
			previous_PES_packet_CRC = bitstream.read_bits(16);
		}

		if(PES_extension_flag)
		{
			PES_private_data_flag = (bool)bitstream.read_bits(1);
			pack_header_field_flag = (bool)bitstream.read_bits(1);
			program_packet_sequence_counter_flag = (bool)bitstream.read_bits(1);
			PSTD_buffer_flag = (bool)bitstream.read_bits(1);
			bitstream.skip_bits(3);
			PES_extension_flag_2 = (bool)bitstream.read_bits(1);

			if(PES_private_data_flag)
			{
				PES_private_data.push_back(bitstream.read_bits(32));
				PES_private_data.push_back(bitstream.read_bits(32));
				PES_private_data.push_back(bitstream.read_bits(32));
				PES_private_data.push_back(bitstream.read_bits(32));
			}

			if(pack_header_field_flag)
			{
				pack_field_length = bitstream.read_bits(8);
				for(int i = 0; i < pack_field_length; i++)
				{
					bitstream.skip_bits(8);
				}
			}

			if(program_packet_sequence_counter_flag)
			{
				bitstream.skip_bits(1);
				program_packet_sequence_counter = bitstream.read_bits(7);
				bitstream.skip_bits(1);
				MPEG1_MPEG2_identifier = bitstream.read_bits(1);
				original_stuff_length = bitstream.read_bits(6);
			}

			if(PSTD_buffer_flag)
			{
				marker = bitstream.read_bits(2);
				pes_assert(marker == 0x1);
				PSTD_buffer_scale = bitstream.read_bits(1);
				PSTD_buffer_size = bitstream.read_bits(13);
			}

			if(PES_extension_flag_2)
			{
				bitstream.skip_bits(1);
				PES_extension_field_length = bitstream.read_bits(7);
				for(int i = 0; i < PES_extension_field_length; i++)
				{
					bitstream.skip_bits(8);
				}
			}
		}

		while(true)
		{
			int tmp = bitstream.peek_bits(8);
			if(tmp == 0xff)
			{
				stuffing_byte.push_back(bitstream.read_bits(8));
			}
			else
				break;
		}

		pes_data_start_offset = bitstream.get_in_byte_offset();
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "header at %d, Data at %d", pes_header_start_offset, pes_data_start_offset);

		/*
		 *	for (i = 0; i < N2; i++) {
		 *	PES_packet_data_byte
		 *	}
		 */
		for(int i = 0; i < DATA_BYTES_STORAGE; i++)
			PES_packet_data_byte.push_back((unsigned char)bitstream.read_bits(8));

		bitstream.skip_bytes(pes_data_start_offset, 0);
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "%s", bitstream.get_next_16_bytes());
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "%s", bitstream.get_next_16_bytes());
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "%s", bitstream.get_next_16_bytes());

	}

	else if(stream_id == stream_id_enum::program_stream_map
			|| stream_id == stream_id_enum::private_stream_2
			|| stream_id == stream_id_enum::ECM_stream
			|| stream_id == stream_id_enum::EMM_stream
			|| stream_id == stream_id_enum::program_stream_directory
			|| stream_id == stream_id_enum::DSMCC_stream
			|| stream_id == stream_id_enum::H222_1_type_E
			)
	{
		pes_data_start_offset = bitstream.get_in_byte_offset();
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "header at %d, Data at %d", pes_header_start_offset, pes_data_start_offset);
		for(int i = 0; i < DATA_BYTES_STORAGE; i++)
			PES_packet_data_byte.push_back((unsigned char)bitstream.read_bits(8));

		bitstream.skip_bytes(pes_data_start_offset, 0);
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "%s", bitstream.get_next_16_bytes());
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "%s", bitstream.get_next_16_bytes());
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "%s", bitstream.get_next_16_bytes());
	}
	else if(stream_id == stream_id_enum::padding_stream)
	{
		for(int i = 0; i < PES_packet_length; i++)
		{
			padding_byte.push_back((char)bitstream.read_bits(8));
		}
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "%s", bitstream.get_next_16_bytes());
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "%s", bitstream.get_next_16_bytes());
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "%s", bitstream.get_next_16_bytes());
	}
}

ParsePESPacket::ParsePESPacket() {
	mycat = log4c_category_get("tsparser.pespacket");
}

ParsePESPacket::~ParsePESPacket() {
	// TODO Auto-generated destructor stub
}

long long ParsePESPacket::get_PTS()
{
	return PTS;
}



long long ParsePESPacket::get_DTS()
{
	return DTS;
}

std::vector<unsigned char>& ParsePESPacket::get_data_bytes()
{
	return PES_packet_data_byte;
}


