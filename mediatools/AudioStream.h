/*
 * AudioStream.h
 *
 *  Created on: Jul 17, 2014
 *      Author: satram
 */

#ifndef AUDIOSTREAM_H_
#define AUDIOSTREAM_H_

#include "mt_common.h"


class AudioPktInfo
{
	bool PUSI_flag;
	long long pts;
	long long dts;
	unsigned int duration_pts_ms;
	unsigned int duration_dts_ms;
	int byte_offset;
	int pkt_count;

public:
	AudioPktInfo(TsPacket *ts);
	~AudioPktInfo();
	void set_prev(AudioPktInfo *prev);
	friend class AudioStream;
};


class AudioStream: public ElementaryStream
{
	log4c_category_t *mycat;

	std::list<AudioPktInfo *> pkt_list;
	AudioPktInfo *prev;

	AUDIO_STREAM_TYPE stream_type;
	int audio_pid;
	int audio_pkt_count;

public:
	AudioStream();
	virtual ~AudioStream();
	void start_recording(int streamtype, int pid);
	void insert_pkt(TsPacket *pkt);
	bool validate_pid(int pid);
	void print_stats();
};

#endif /* AUDIOSTREAM_H_ */
