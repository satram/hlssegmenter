/*
 * ParseTsHeader.h
 *
 *  Created on: Jul 2, 2014
 *      Author: satram
 */

#ifndef PARSETSHEADER_H_
#define PARSETSHEADER_H_

#include "Common.h"

class ParseTsHeader {

	log4c_category_t* mycat;

	char sync_byte;
	int transport_error_indicator;
	bool payload_unit_start_indicator;
	int transport_priority;
	unsigned int PID;
	int transport_scrambling_control;
	int adaptation_field_control;
	int continuity_counter;

public:
	ParseTsHeader();
	virtual ~ParseTsHeader();
	void printTsHeader();
	void input_bitstream(Bitstream &bitstream);

	int get_PID();
	bool get_PUSI();
	int get_adapation_flag();
	int get_cc();
};

#endif /* PARSETSHEADER_H_ */
