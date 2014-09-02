/*
 * PatParse.cpp
 *
 *  Created on: Jul 3, 2014
 *      Author: satram
 */

#include "PatParse.h"
#include "Bitstream.h"
#include "SectionHeader.h"

void PatParse::input_bitstream(Bitstream & bitstream, int current_pid)
{
	log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "PAT Parsing");

	header->input_bitstream(bitstream, mycat);
    int section_length = header->get_section_length();

    section_length = section_length - 5 - 4;

    for(int i = 0;  ;i++){
    	unsigned short pgm_num = bitstream.read_bits(16);
    	std::vector<unsigned short>::iterator it = std::find(program_number.begin(), program_number.end(), pgm_num);
    	if(it != program_number.end())
    	{
    		log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "repetitive program number %x - breaks loop", pgm_num);
    		break;
    	}
        program_number.push_back(pgm_num);
        log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "program_number %x", pgm_num);
        bitstream.skip_bits(3);
        if(program_number[i] == 0x0){
        	unsigned short net_pid = bitstream.read_bits(13);
        	if(net_pid >= 0 && net_pid <= MAX_PID)
        	{
                network_PID.push_back(net_pid);
                log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "network_PID %x", net_pid);
        	}
        }else{
        	unsigned short pmt_pid = bitstream.read_bits(13);
        	if(pmt_pid >= 0 && pmt_pid <= MAX_PID)
        	{
				program_map_PID.push_back(pmt_pid);
				log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "program_map_PID %x", pmt_pid);
				if(pmt_pid == current_pid)
					break;
        	}
        }
        section_length = section_length - 4;
        if(section_length <= 4)
            break;
    }
    crc = bitstream.read_bits(32);
}

PatParse::PatParse()
{
	header = new SectionHeader();
	mycat = log4c_category_get("tsparser.patpacket");
}

PatParse::~PatParse()
{
	delete header;
}

/*
 * always return the first program stream's PMT PID
 */

int PatParse::get_pmt_pid()
{
	if(!program_map_PID.empty())
	{
		log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "returning pmt pid as %d", program_map_PID[0]);
		return program_map_PID[0];
	}
	else
	{
		return 0;
	}
}


