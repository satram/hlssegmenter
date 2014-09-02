/*
 * ParseAdaptationField.h
 *
 *  Created on: Jul 3, 2014
 *      Author: satram
 */

#ifndef PARSEADAPTATIONFIELD_H_
#define PARSEADAPTATIONFIELD_H_

#include "mt_common.h"

class ParseAdaptationField {

   log4c_category_t* mycat;

	int adaptation_field_length;
	bool discontinuity_indicator;
	bool random_access_indicator;
	bool elementary_stream_priority_indicator;
	bool PCR_flag;
	bool OPCR_flag;
	bool splicing_point_flag;
	bool transport_private_data_flag;
	bool adaptation_field_extension_flag;

	long long program_clock_reference_base;
	int program_clock_refrence_extension;

	long long original_program_clock_reference_base;
	int original_program_clock_refrence_extension;

	int splice_countdown;

	int transport_private_data_length;
	std::vector<char> private_data_byte;

	int adaptation_field_extension_length;
	bool ltw_flag;
	bool piecewise_rate_flag;
	bool seamless_splice_flag;

	bool ltw_valid_flag;
	int ltw_offset;

	int piecewise_rate;

	int splice_type;
	int DTS_next_AU;



public:
	ParseAdaptationField();
	virtual ~ParseAdaptationField();
	void input_bitstream(Bitstream &bitstream);
	int get_length();
};



#endif /* PARSEADAPTATIONFIELD_H_ */
