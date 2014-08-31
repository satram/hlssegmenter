/*
 * SectionHeader.h
 *
 *  Created on: Jul 24, 2014
 *      Author: satram
 */

#ifndef SECTIONHEADER_H_
#define SECTIONHEADER_H_

#include "Common.h"

class SectionHeader {
	unsigned char pointer_field;
	char table_id;
	char section_syntax_indicator;
	int section_length;
	int transport_stream_id;
	int version_number;
	int current_next_indicator;
	int section_number;
	int last_section_number;

public:
	SectionHeader();
	virtual ~SectionHeader();
	void input_bitstream(Bitstream &bitstream, log4c_category_t *mycat);
	int get_section_length();
};

#endif /* SECTIONHEADER_H_ */
