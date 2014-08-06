/*
 * ParseAdaptationField.cpp
 *
 *  Created on: Jul 3, 2014
 *      Author: satram
 */

#include "ParseAdaptationField.h"

ParseAdaptationField::~ParseAdaptationField()
{
}

ParseAdaptationField::ParseAdaptationField()
{
	mycat = log4c_category_get("tsparser.adaptationfield");
}

void ParseAdaptationField::input_bitstream(Bitstream &bitstream)
{
	adaptation_field_length = bitstream.read_bits(8);
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "adaptation_field_length %d", adaptation_field_length);

	if(adaptation_field_length > 0)
	{
		discontinuity_indicator = (bool)bitstream.read_bits(1);
		random_access_indicator = (bool)bitstream.read_bits(1);
		elementary_stream_priority_indicator = (bool)bitstream.read_bits(1);
		PCR_flag = (bool)bitstream.read_bits(1);
		OPCR_flag = (bool)bitstream.read_bits(1);
		splicing_point_flag = (bool)bitstream.read_bits(1);
		transport_private_data_flag = (bool)bitstream.read_bits(1);
		adaptation_field_extension_flag = (bool)bitstream.read_bits(1);
		//log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "adaptation_field_extension_flag %d", adaptation_field_extension_flag);

		if(PCR_flag)
		{
			log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "pcr flag related parsing");
			program_clock_reference_base = bitstream.read_bits(32) << 1;
			program_clock_reference_base |= (bitstream.read_bits(1));
			bitstream.skip_bits(6);
			program_clock_refrence_extension = bitstream.read_bits(9);
		}

		if(OPCR_flag)
		{
			log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "opcr flag related parsing");
			original_program_clock_reference_base = bitstream.read_bits(32) << 1;
			original_program_clock_reference_base |= (bitstream.read_bits(1));
			bitstream.skip_bits(6);
			original_program_clock_refrence_extension = bitstream.read_bits(9);
		}

		if(splicing_point_flag)
		{
			log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "splice flag related parsing");
			splice_countdown = bitstream.read_bits(8);
		}

		if(transport_private_data_flag)
		{
			log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "transport private flag related parsing");

			transport_private_data_length = bitstream.read_bits(8);
			for(int i = 0; i < transport_private_data_length; i++)
			{
				private_data_byte.push_back((char)bitstream.read_bits(8));
			}
		}

		if(adaptation_field_extension_flag)
		{
			log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "extension flag related parsing");

			adaptation_field_extension_length = bitstream.read_bits(8);
			ltw_flag = bitstream.read_bits(1);
			piecewise_rate_flag = bitstream.read_bits(1);
			seamless_splice_flag = bitstream.read_bits(1);
			bitstream.skip_bits(5);

			if(ltw_flag)
			{
				ltw_valid_flag = bitstream.read_bits(1);
				ltw_offset = bitstream.read_bits(15);
			}

			if(piecewise_rate_flag)
			{
				bitstream.skip_bits(2);
				piecewise_rate = bitstream.read_bits(22);
			}

			if(seamless_splice_flag)
			{
				splice_type = bitstream.read_bits(4);
				DTS_next_AU = bitstream.read_bits(3) << 30;
				bitstream.skip_bits(1);
				DTS_next_AU |= (bitstream.read_bits(15) << 15);
				bitstream.skip_bits(1);
				DTS_next_AU |= bitstream.read_bits(15);
				bitstream.skip_bits(1);
			}
		}
		//int bits_remaining = adaptation_field_length - start_offset;
		//log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "skip_bits %d", bits_remaining);
		//bitstream.skip_bits(bits_remaining);
	}
}

int ParseAdaptationField::get_length()
{
	return adaptation_field_length;
}


