/*
 * ParseTsHeader.cpp
 *
 *  Created on: Jul 2, 2014
 *      Author: satram
 */

#include "ParseTsHeader.h"
#include "Bitstream.h"

ParseTsHeader::ParseTsHeader() {
	mycat = log4c_category_get("tsparser.tsheader");
}

ParseTsHeader::~ParseTsHeader() {
}

void ParseTsHeader::printTsHeader()
{
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "sync byte %x", sync_byte);
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "PUSI flag %d, PID %d", payload_unit_start_indicator, PID);
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "continuity counter %d, adaptation_field_control %d", continuity_counter, adaptation_field_control );
}

int ParseTsHeader::get_PID()
{
	return PID;
}



void ParseTsHeader::input_bitstream(Bitstream & bitstream)
{
	int start_offset = bitstream.get_in_byte_offset();
	sync_byte = bitstream.read_bits(8);
	//log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "got sync_byte as %x", sync_byte);
	if(sync_byte != 0x47 && sync_byte != 0x48)
	{
		bitstream.seek_pos(start_offset);
		bitstream.calibrate_ts_packet_size();
		sync_byte = bitstream.read_bits(8);
	}
	transport_error_indicator = bitstream.read_bits(1);
	payload_unit_start_indicator = (bool)bitstream.read_bits(1);
	transport_priority = bitstream.read_bits(1);
	PID = bitstream.read_bits(13);
	transport_scrambling_control = bitstream.read_bits(2);
	adaptation_field_control = bitstream.read_bits(2);
	continuity_counter = bitstream.read_bits(4);
	printTsHeader();
}

int ParseTsHeader::get_cc()
{
	return continuity_counter;
}



bool ParseTsHeader::get_PUSI()
{
	return payload_unit_start_indicator;
}



int ParseTsHeader::get_adapation_flag()
{
	return adaptation_field_control;
}


