/*
 * ElementaryStream.h
 *
 *  Created on: Jul 18, 2014
 *      Author: satram
 */

#ifndef ELEMENTARYSTREAM_H_
#define ELEMENTARYSTREAM_H_

#include "Common.h"

class ElementaryStream {
public:
//	ElementaryStream();
//	virtual ~ElementaryStream();

	virtual void start_recording(int streamtype, int pid);
	virtual void insert_pkt(TsPacket *pkt);
	virtual bool validate_pid(int pid);
	virtual void print_stats();

};

inline void ElementaryStream::start_recording(int streamtype, int pid)
{
}



inline void ElementaryStream::insert_pkt(TsPacket *pkt)
{
}



inline bool ElementaryStream::validate_pid(int pid)
{
	return false;
}

inline void ElementaryStream::print_stats()
{

}

#endif /* ELEMENTARYSTREAM_H_ */
