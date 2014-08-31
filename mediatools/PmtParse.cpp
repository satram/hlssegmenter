/*
 * PmtParse.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: satram
 */

#include "PmtParse.h"

void PmtParse::input_bitstream(Bitstream & bitstream)
{
    //int start_offset = bitstream.get_in_byte_offset();
    log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "PMT Parsing");

    header->input_bitstream(bitstream, mycat);
    int section_length = header->get_section_length();

    bitstream.skip_bits(3);
    PCR_PID = bitstream.read_bits(13);
    bitstream.skip_bits(4);
    program_info_length = bitstream.read_bits(12);

    section_length = section_length - 5 -4;


    while(1){
        esinfo.push_back(elementary_stream_info(bitstream, mycat));
        section_length = section_length - 4;
          if(section_length <= 4)
              break;
    }
    CRC_32 = bitstream.read_bits(32);
}

PmtParse::PmtParse()
{
	header = new SectionHeader();
	mycat = log4c_category_get("tsparser.pmtpacket");
}

PmtParse::~PmtParse() {
	delete header;
}

elementary_stream_info::elementary_stream_info(Bitstream & bitstream, log4c_category_t* mycat)
{
	stream_type = bitstream.read_bits(8);
	bitstream.skip_bits(3);
	elementary_PID = bitstream.read_bits(13);
	bitstream.skip_bits(4);
	ES_info_length = bitstream.read_bits(12);
	log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "esinfo streamtype %d elementary_PID %d ESlength %d", stream_type, elementary_PID, ES_info_length);
}



elementary_stream_info::~elementary_stream_info()
{
	// TODO Auto-generated destructor stub
}

int PmtParse::get_audio_pid(int &streamtype)
{
	for (unsigned int i = 0; i < esinfo.size(); i++)
	{
		switch(esinfo[i].get_stream_type())
		{
		case 0x3: //mpeg1 audio
		case 0x4: //mpeg2 audio
		case 0xf: //mpeg2 audio, ADTS
		case 0x11: //mpeg4 audio, LATM
			log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "returning audio pid as %d", esinfo[i].get_pid());
			streamtype = esinfo[i].get_stream_type();
			return esinfo[i].get_pid();
			break;
		default:
			break;
		}
	}
	return 0;
}



int PmtParse::get_video_pid(int &streamtype)
{
	for (unsigned int i = 0; i < esinfo.size(); i++)
	{
		switch(esinfo[i].get_stream_type())
		{
		case 0x1: //mpeg1 videp
		case 0x2: //mpeg2 video
		case 0x9: //H.262
		case 0x10: //mpeg4 video
		case 0x1b: //H264
			log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "returning video pid as %d", esinfo[i].get_pid());
			streamtype = esinfo[i].get_stream_type();
			return esinfo[i].get_pid();
			break;
		default:
			break;
		}
	}
	return 0;
}

int elementary_stream_info::get_stream_type()
{
	return stream_type;
}



int elementary_stream_info::get_pid()
{
	return elementary_PID;
}








