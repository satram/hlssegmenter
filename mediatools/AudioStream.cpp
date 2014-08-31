/*
 * AudioStream.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: satram
 */

#include "AudioStream.h"

AudioStream::AudioStream() {
	mycat = log4c_category_get("tsparser.elementarystream");
	prev = NULL;
}

AudioStream::~AudioStream() {
	for(auto it = pkt_list.begin(), ite = pkt_list.end(); it != ite; it++)
		delete (*it);
}

void AudioStream::start_recording(int streamtype, int pid)
{
	stream_type = (AUDIO_STREAM_TYPE)streamtype;
	audio_pid = pid;
	audio_pkt_count = 0;
}



void AudioStream::insert_pkt(TsPacket *pkt)
{
	AudioPktInfo *curr = new AudioPktInfo(pkt);
	if(curr->PUSI_flag)
	{
		curr->set_prev(prev);
		prev = curr;
	}
	pkt_list.push_back(curr);
	audio_pkt_count++;
}



bool AudioStream::validate_pid(int pid)
{
	if((pid == mpeg1audio) ||
	(pid == mpeg2audio) ||
	(pid == mpeg2audio_adts) ||
	(pid == mpeg4audio_latm))
	{
		return true;
	}
	else
	{
		return false;

	}
}

void AudioStream::print_stats()
{
	//log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "Audio Frame Stats");

	for(auto it = pkt_list.begin(), ite = pkt_list.end(); it != ite; it++)
	{
		if((*it)->PUSI_flag)
		{
			log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "Audio pkt %d offset %d PTS %llu Duration %d", (*it)->pkt_count, (*it)->byte_offset, (*it)->pts, (*it)->duration_pts_ms);
		}
	}
}


AudioPktInfo::AudioPktInfo(TsPacket *ts)
{
	pts = ts->get_PTS();
	dts = ts->get_DTS();
	byte_offset = ts->get_start_offset();
	PUSI_flag = ts->get_PUSI_flag();
	pkt_count = ts->get_count();
}



AudioPktInfo::~AudioPktInfo()
{
}


void AudioPktInfo::set_prev(AudioPktInfo *prev)
{
	duration_pts_ms = 0;
	duration_dts_ms = 0;
	if(prev != NULL)
	{
		duration_pts_ms = (unsigned int)((pts - prev->pts)/TS_TIMESCALE_MILLISEC);
		duration_dts_ms = (unsigned int)((dts - prev->dts)/TS_TIMESCALE_MILLISEC);
	}
}
