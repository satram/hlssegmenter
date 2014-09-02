/*
 * TsParserTestMain.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: satram
 */

#include "ParseTsStream.h"


int ts_parser_fileinput(char *argv[])
{
	ParseTsStream input_ts_stream;

	//filename is input
	std::string filename(argv[1]);
	input_ts_stream.open(filename);

	input_ts_stream.parse_bytestream();
	input_ts_stream.print_pid_list();
	input_ts_stream.print_stats();

	input_ts_stream.close();
	return 0;
}



void ts_parser_rdbuf_input(char *argv[])
{
    std::ifstream infile;
    infile.open(argv[1], std::ios::in | std::ios::binary);
    if(infile.is_open()){
        ParseTsStream input_ts_stream;

        //rdbuf is the input
        input_ts_stream.open(infile.rdbuf());

        input_ts_stream.parse_bytestream();
        input_ts_stream.print_pid_list();
        input_ts_stream.print_stats();
        input_ts_stream.close();
        infile.close();
    }
}


void ts_parser_fullbuf_input(char *argv[])
{
    std::ifstream infile;
    char *inp_buffer = NULL;
    int filesize = 0;

    infile.open(argv[1], std::ios::in | std::ios::binary | std::ios::ate);
    if(infile.is_open())
    {
        filesize = infile.tellg();
        inp_buffer = new char[filesize];
        infile.seekg(0, std::ios::beg);
        infile.read(inp_buffer, filesize);
        infile.close();
    }

    if(inp_buffer != NULL)
    {
        ParseTsStream input_ts_stream;
        input_ts_stream.open(inp_buffer, filesize);
        input_ts_stream.parse_bytestream();
        input_ts_stream.print_pid_list();
        input_ts_stream.print_stats();
        input_ts_stream.close();
        delete inp_buffer;
    }

    return;
}



#define INP_BUF_SIZE (100 * TS_PKT_SIZE_BYTES)

void ts_parser_partialbuf_input(char *argv[])
{
    std::ifstream infile;
    infile.open(argv[1], std::ios::in | std::ios::binary);
    char *inp_buffer = new char[INP_BUF_SIZE];
    if(infile.is_open())
    {
        ParseTsStream input_ts_stream;
        while(!infile.eof())
        {
        	infile.read(inp_buffer, INP_BUF_SIZE);
            input_ts_stream.open(inp_buffer, INP_BUF_SIZE);
            input_ts_stream.parse_bytestream();
            input_ts_stream.print_pid_list();
            input_ts_stream.print_stats();
            input_ts_stream.close();
        }
        infile.close();
    }
    delete inp_buffer;
}

enum TESTCASE
{
	FILE_INPUT,
	RDBUF_INPUT,
	FULLBUF_INPUT,
	PARTIAL_BUF_INPUT
};


int main(int argc, char* argv[])
{
	TESTCASE test = PARTIAL_BUF_INPUT;
	Profiler wrapper("wrapper");
	wrapper.start_timer();
	switch(test)
	{
	case FILE_INPUT:
		ts_parser_fileinput(argv);
		break;
	case RDBUF_INPUT:
	    ts_parser_rdbuf_input(argv);
	    break;
	case FULLBUF_INPUT:
		ts_parser_fullbuf_input(argv);
		break;
	case PARTIAL_BUF_INPUT:
		ts_parser_partialbuf_input(argv);
	    break;
	default:
		break;
	}
	wrapper.record_elapsed_time();
	wrapper.print_stats();
	return 0;
}
