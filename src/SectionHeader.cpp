/*
 * SectionHeader.cpp
 *
 *  Created on: Jul 24, 2014
 *      Author: satram
 */

#include "SectionHeader.h"

SectionHeader::SectionHeader() {
	// TODO Auto-generated constructor stub

}

SectionHeader::~SectionHeader() {
	// TODO Auto-generated destructor stub
}

void SectionHeader::input_bitstream(Bitstream & bitstream, log4c_category_t *mycat)
{
	pointer_field = bitstream.read_bits(8);
	table_id = bitstream.read_bits(8);
    section_syntax_indicator = bitstream.read_bits(1);
    if(section_syntax_indicator != 1)
       	throw(std::runtime_error("sectionheader: section_syntax_indicator != 1"));
    if(bitstream.read_bits(1) != 0)
    	throw(std::runtime_error("sectionheader: reserved bit(10) != 0"));
    bitstream.skip_bits(2);
    log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "table_id %d, section_syntax_indicator %d", table_id, section_syntax_indicator);

    section_length = bitstream.read_bits(12);
    transport_stream_id = bitstream.read_bits(16);
    bitstream.skip_bits(2);
    log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "section_length %d, transport_stream_id %d", section_length, transport_stream_id);

    version_number = bitstream.read_bits(5);
    current_next_indicator = bitstream.read_bits(1);
    section_number = bitstream.read_bits(8);
    last_section_number = bitstream.read_bits(8);
    log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "version_number %d (indicator %d), sect_num %d last_sectnum %d", version_number, current_next_indicator, section_number, last_section_number);

}



int SectionHeader::get_section_length()
{
	return section_length;
}


