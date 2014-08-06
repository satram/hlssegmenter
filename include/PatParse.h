/*
 * PatParse.h
 *
 *  Created on: Jul 3, 2014
 *      Author: satram
 */

#ifndef PATPARSE_H_
#define PATPARSE_H_

#include "Common.h"


class PatParse {

	log4c_category_t* mycat;

	SectionHeader *header;
	int crc;

	std::vector<unsigned short> program_number;
	std::vector<unsigned short> network_PID;
	std::vector<unsigned short> program_map_PID;

public:
	PatParse();
	virtual ~PatParse();
	int get_pmt_pid();
    void input_bitstream(Bitstream & bitstream, int current_pid);
};

#endif /* PATPARSE_H_ */
