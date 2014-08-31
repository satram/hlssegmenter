/*
 * TsPacket.cpp
 *
 *  Created on: Jul 16, 2014
 *      Author: satram
 */

#include "TsPacket.h"

class TS_exception: public std::exception
{
public:
	virtual const char * what() const throw()
	{
		return nullptr;
	};
};


TsPacket::TsPacket(int ts_packet_count){
	mycat = log4c_category_get("tsparser.tspacket");
	count = ts_packet_count;
	tsheader = new ParseTsHeader();
	pes_packet = new ParsePESPacket();
	adaptation_header = new ParseAdaptationField();
}

TsPacket::~TsPacket() {
	delete tsheader;
	delete pes_packet;
	delete adaptation_header;
}

void TsPacket::input_bitstream(Bitstream & bitstream)
{
	//bitstream.print_packet();

    data_packet_start_byte_offset = bitstream.get_in_byte_offset();
    ts_packet_size = bitstream.get_ts_packet_size();

    tsheader->input_bitstream(bitstream);
    pid = tsheader->get_PID();
    payload_unit_start_indicator = tsheader->get_PUSI();
    adaptation_field_control = tsheader->get_adapation_flag();
    if(adaptation_field_control == 0x2 || adaptation_field_control == 0x3){
		int start_offset = bitstream.get_in_byte_offset();
		adaptation_header->input_bitstream(bitstream);
		int length = adaptation_header->get_length();
		bitstream.skip_bytes(start_offset, length + LENGTH_VAR_BYTES);
	}
}

int TsPacket::get_pid()
{
	return(pid);
}

void TsPacket::parse_data_byte(Bitstream & bitstream, bool parse_data)
{
	if(adaptation_field_control == 0x1 || adaptation_field_control == 0x3)
	{
		switch(pid)
		{
		case 1:
		case 2:
			//conditional access & transport stream description table
		case 0x1fff:
			//null packet
			skip_to_end(bitstream);
			break;


		default:
			if(payload_unit_start_indicator && parse_data)
			{
				pes_packet->input_bitstream(bitstream);
				skip_to_end(bitstream);
				log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "PTS %llu DTS %llu", pes_packet->get_PTS(), pes_packet->get_DTS());
				//std::cout << "PTS " << pes_packet->get_PTS() << std::endl;
				//std::cout << "DTS " << pes_packet->get_DTS() << std::endl;
			}
			else
			{
				//bitstream.skip_bytes(data_packet_start_byte_offset, TS_PKT_SIZE_BYTES);
				throw TS_exception();
			}
		}
	}
	else
	{
		throw TS_exception();
	}
}

void TsPacket::skip_to_end(Bitstream & bitstream)
{
	log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "skip_to_end %d bytes @ %d offset", ts_packet_size, data_packet_start_byte_offset);
	bitstream.skip_bytes_calibrate(data_packet_start_byte_offset, ts_packet_size);
}

long long TsPacket::get_DTS()
{
	if(payload_unit_start_indicator)
		return pes_packet->get_DTS();
	else
		return 0;
}



bool TsPacket::get_PUSI_flag()
{
	return payload_unit_start_indicator;
}



long long TsPacket::get_PTS()
{
	if(payload_unit_start_indicator)
		return pes_packet->get_PTS();
	else
		return 0;
}



int TsPacket::get_count()
{
	return count;
}

int TsPacket::get_start_offset()
{
	return data_packet_start_byte_offset;
}


ParsePESPacket *TsPacket::get_pes_packet()
{
	return pes_packet;
}





