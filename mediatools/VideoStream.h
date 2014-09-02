/*
 * VideoStream.h
 *
 *  Created on: Jul 17, 2014
 *      Author: satram
 */

#ifndef VIDEOSTREAM_H_
#define VIDEOSTREAM_H_

#include "mt_common.h"
#include "VideoPktInfo.h"



class VideoStream: public ElementaryStream
{
	log4c_category_t *mycat;

	std::list<VideoPktInfo *> pkt_list;

	VideoPktInfo *prev;

	VIDEO_STREAM_TYPE stream_type;

	int video_pid;
	int video_pkt_count;

public:
	VideoStream();
	virtual ~VideoStream();
	void start_recording(int streamtype, int pid);
	void insert_pkt(TsPacket *pkt);
	bool validate_pid(int pid);
	void print_stats();
	std::list<VideoPktInfo *> &get_pkt_info();
};

#endif /* VIDEOSTREAM_H_ */
