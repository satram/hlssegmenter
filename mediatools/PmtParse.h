/*
 * PmtParse.h
 *
 *  Created on: Jul 7, 2014
 *      Author: satram
 */

#ifndef PMTPARSE_H_
#define PMTPARSE_H_

#include "mt_common.h"



class elementary_stream_info {
	int stream_type;
	int elementary_PID;
	int ES_info_length;
	char *descriptor;
public:
	elementary_stream_info(Bitstream &bitstream, log4c_category_t* mycat);
	virtual ~elementary_stream_info();
	int get_stream_type();
	int get_pid();
};

class PmtParse {

	log4c_category_t* mycat;

	SectionHeader *header;

	int PCR_PID;
	int program_info_length;

	std::vector<elementary_stream_info> esinfo;

	int CRC_32;


public:
	PmtParse();
	virtual ~PmtParse();
	int get_video_pid(int &streamtype);
	int get_audio_pid(int &streamtype);
    void input_bitstream(Bitstream & bitstream);
};

#endif /* PMTPARSE_H_ */
