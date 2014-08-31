/*
 * Bitstream.cpp
 *
 *  Created on: Jul 2, 2014
 *      Author: satram
 */

#include "Bitstream.h"

Bitstream::Bitstream() {
	mycat = log4c_category_get("tsparser.bitstream");
	log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "Bitstream constructor called");
	readBufferSize = sizeof(int) * BYTE_SIZE;
	writeBufferSize = sizeof(int) * BYTE_SIZE;
	ts_packet_size = 0;
	start_offset = 0;
	inStream = NULL;
	sstream = NULL;
	log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "readBufferSize %d, writeBufferSize %d", readBufferSize, writeBufferSize);
}

Bitstream::~Bitstream() {

}


//file operations

void Bitstream::close()
{
	if(infile.is_open())
	{
		infile.close();
	}
	if(inStream != NULL)
	{
		delete inStream;
		inStream = NULL;
	}
	if(sstream != NULL)
	{
		delete sstream;
		sstream = NULL;
	}
}

void Bitstream::open(std::string &filename)
{
	infile.open(filename.c_str(), std::ios::in | std::ios::binary);
	if(infile.is_open())
	{
		inStream = new std::istream(infile.rdbuf());
	    prepare_input_stream();
	}
}

void Bitstream::open(std::streambuf *rdbuf)
{
	inStream = new std::istream(rdbuf);
    prepare_input_stream();
}

void Bitstream::open(const char *buf, int length)
{
    sstream = new std::istringstream(std::string(buf, length));
	inStream = new std::istream(sstream->rdbuf());
    prepare_input_stream();
}



//istream operations

void Bitstream::prepare_input_stream()
{
	inStream->seekg(0, std::ios::end);
    inBufSize = inStream->tellg();
    log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "input buffer size %d", inBufSize);
    inStream->seekg(0, std::ios::beg);
    calibrate_ts_packet_size();
}

void Bitstream::read_stream()
{
	if(!inStream->eof())
	{
		unsigned char tmp[4] = {0,0,0,0};
		inStream->read((char *)tmp, sizeof(int));
		readBuffer = (tmp[0] << 24) | (tmp[1] << 16) | (tmp[2] << 8) | (tmp[3]);
		readBufferBitPos = readBufferSize;
		log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "read_file, updated readbuffer is %x", readBuffer);
	}
}

void Bitstream::read_stream(int &inpbuffer)
{
    inStream->read((char *)&inpbuffer, sizeof(int));
}

void Bitstream::calibrate_ts_packet_size()
{
	unsigned char tmp;
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "searching for start_offset at %d", (int)inStream->tellg());
	while(1)
	{
		inStream->read((char *)&tmp, 1);
		if(tmp == 0x47 || tmp == 0x48)
		{
			start_offset = (int)inStream->tellg() - 1;
			log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "calibrate - startcode %x start_offset %d", tmp, start_offset);
			break;
		}
	}
	//got to default boundary
	inStream->seekg(TS_PKT_SIZE_BYTES + start_offset, std::ios::beg);
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "searching for ts_pkt_size at pos %d", (int)inStream->tellg());
	while(1)
	{
		inStream->read((char *)&tmp, 1);
		if(tmp == 0x47 || tmp == 0x48)
		{
			ts_packet_size = (int)inStream->tellg() - 1 - start_offset;
			log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "calibrate - following-startcode %x ts_packet_size %d", tmp, ts_packet_size);
			break;
		}
	}
	inStream->seekg(start_offset, std::ios::beg);
	read_stream();
}




/*
 * read_bits length has to be <= WORD_SIZE
 */
unsigned int Bitstream::read_bits(int length)
{
	unsigned int res, res1;
	unsigned int mask = 0xffffffff;

	if(length <= readBufferBitPos)
	{
		mask = mask >> (readBufferSize - length);
		readBufferBitPos -= length;
		mask = mask << readBufferBitPos;
		res = readBuffer & mask;
		res = res >> readBufferBitPos;
		log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "readBuffer %x Pos %d mask %x, read_bits %d, result %x", readBuffer, readBufferBitPos, mask, length,  res);
	}
	else
	{
		int rembits;
		mask = (long long)mask >> (readBufferSize - readBufferBitPos);
		//log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "mask %x, readBufferSize %d, readBufferBitPos %d", mask, readBufferSize, readBufferBitPos);
		res = readBuffer & mask;
		res = res << (length - readBufferBitPos);
		rembits = length - readBufferBitPos;
		//log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "mask %x, read_bits %d, res %x", mask, readBufferBitPos, res);

		read_stream();
		//log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "readBuffer %x Pos %d", readBuffer, readBufferBitPos);
		mask = 0xffffffff;
		mask = mask >> (readBufferSize - rembits);
		readBufferBitPos -= rembits;
		mask = mask << readBufferBitPos;
		res1 = readBuffer & mask;
		res1 = res1 >> readBufferBitPos;
		//log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "mask %x, read_bits %d, res %x", mask, rembits, res1);

		res = res | res1;
		log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "readBuffer %x Pos %d mask %x, read_bits %d, result %x", readBuffer, readBufferBitPos, mask, length,  res);
	}
	return(res);
}

/*
 * peek_bits length has to be <= WORD_SIZE
 */
unsigned int Bitstream::peek_bits(int length)
{
	unsigned int res;
	unsigned int mask = 0xffffffff;

	if(length <= readBufferBitPos)
	{
		mask = mask >> (readBufferSize - length);
		mask = mask << (readBufferBitPos - length);
		res = readBuffer & mask;
		res = res >> (readBufferBitPos - length);
		log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "peek_bits %d mask %x, result %x", length, mask, res);

	}
	else
	{
		throw(std::runtime_error("Can't peek_bits at this pos"));
	}
	return(res);
}

/*
 * skip length has to be <= WORD_SIZE
 */
void Bitstream::skip_bits(int length)
{
	if(length <= readBufferBitPos)
	{
		readBufferBitPos -= length;
	}
	else
	{
		length = length - readBufferBitPos;
		read_stream();
		readBufferBitPos -= length;
	}
}

int Bitstream::get_in_byte_offset()
{
	return ((int)inStream->tellg() - (readBufferBitPos /8));
}

bool Bitstream::is_eof()
{
	return inStream->eof();
}

void Bitstream::skip_bytes(int current_pos, int skip_size_bytes)
{
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "skip_bytes %d from position %d", skip_size_bytes, current_pos);
	inStream->seekg(current_pos, std::ios::beg);
	if(current_pos + skip_size_bytes >= inBufSize)
	{
		char tmp;
		inStream->seekg(0, std::ios::end);
		inStream->read(&tmp, 1);
		return;
	}
	inStream->seekg(skip_size_bytes, std::ios::cur);
	read_stream();
}

void Bitstream::skip_bytes_calibrate(int current_pos, int skip_size_bytes)
{
	skip_bytes(current_pos, skip_size_bytes);
	if(inStream->eof() || (inStream->tellg() == -1))
		return;
	unsigned char start_code = peek_bits(8);
	if(start_code != 0x47 && start_code != 0x48)
	{
		log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "going to calibrate");
		inStream->seekg(current_pos, std::ios::beg);
		calibrate_ts_packet_size();
		inStream->seekg(ts_packet_size, std::ios::cur);
	}
}

int Bitstream::get_ts_packet_size()
{
	if(ts_packet_size != 0)
		return ts_packet_size;
	else
		return TS_PKT_SIZE_BYTES;
}

void Bitstream::seek_pos(int offset)
{
	inStream->seekg(offset, std::ios::beg);
}

void Bitstream::print_packet()
{
	int start_offset = get_in_byte_offset();
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "start_offset %d", start_offset);
	for(int i = 0; i < ts_packet_size;)
	{
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "%s", get_next_16_bytes());
		i = i + 16;
	}
	skip_bytes(start_offset, 0);
}

const char *Bitstream::get_next_16_bytes()
{
	word_ss.clear();
	word_ss.str(std::string());
	word_ss << std::setbase(16) << std::internal << std::setfill('0') ;
	word_ss << std::setw(2) << read_bits(8) << " " ;
	word_ss << std::setw(2) << read_bits(8) << " " ;
	word_ss << std::setw(2) << read_bits(8) << " " ;
	word_ss << std::setw(2) << read_bits(8) << " " ;
	word_ss << std::setw(2) << read_bits(8) << " " ;
	word_ss << std::setw(2) << read_bits(8) << " " ;
	word_ss << std::setw(2) << read_bits(8) << " " ;
	word_ss << std::setw(2) << read_bits(8) << "  " ;

	word_ss << std::setw(2) << read_bits(8) << " " ;
	word_ss << std::setw(2) << read_bits(8) << " " ;
	word_ss << std::setw(2) << read_bits(8) << " " ;
	word_ss << std::setw(2) << read_bits(8) << " " ;
	word_ss << std::setw(2) << read_bits(8) << " " ;
	word_ss << std::setw(2) << read_bits(8) << " " ;
	word_ss << std::setw(2) << read_bits(8) << " " ;
	word_ss << std::setw(2) << read_bits(8) << " " ;
	return word_ss.str().c_str();
}









