/*
 * Bitstream.h
 *
 *  Created on: Jul 2, 2014
 *      Author: satram
 */


#ifndef BITSTREAM_H_
#define BITSTREAM_H_

#include "mt_common.h"



class Bitstream {
    std::ifstream infile;
    std::istream *inStream;
    std::istringstream *sstream;

    std::stringstream word_ss;

    int inBufSize;
    int readBuffer;
    int readBufferSize;
    int readBufferBitPos;

    int outByteOffset;
    int outFileSize;
    int writeBuffer;
    int writeBufferSize;
    int writeBufferBitPos;

    int ts_packet_size;
    int start_offset;

    log4c_category_t* mycat;

    void read_stream();
    void read_stream(int &inpBuffer);
    void prepare_input_stream();

public:
	Bitstream();
	virtual ~Bitstream();
	void open(std::string &filename);
	void open(std::streambuf *rdbuf);
	void open(const char *buf, int length);
	void close();
	unsigned int read_bits(int length);
	unsigned int peek_bits(int length);
	void skip_bits(int length);
	int get_in_byte_offset();
	bool is_eof();

	void skip_bytes(int current_pos, int skip_size_bytes);
	void skip_bytes_calibrate(int current_pos, int skip_size_bytes);

	void calibrate_ts_packet_size();
	int get_ts_packet_size();
	void seek_pos(int offset);

	const char * get_next_16_bytes();
	void print_packet();
};

#endif /* BITSTREAM_H_ */
