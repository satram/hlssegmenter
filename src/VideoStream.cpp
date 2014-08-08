/*
 * VideoStream.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: satram
 */

#include "VideoStream.h"




VideoStream::VideoStream()
{
	mycat = log4c_category_get("tsparser.elementarystream");
	prev = NULL;
}

VideoStream::~VideoStream()
{
	for(auto it = pkt_list.begin(), ite = pkt_list.end(); it != ite; it++)
		delete (*it);
}

void VideoStream::start_recording(int streamtype, int pid)
{
	video_pid = pid;
	stream_type = (VIDEO_STREAM_TYPE)streamtype;
	video_pkt_count = 0;
}

void VideoStream::insert_pkt(TsPacket *pkt)
{
	VideoPktInfo *curr = new VideoPktInfo(pkt);
	if(curr->PUSI_flag)
	{
		curr->set_prev(prev);
		prev = curr;
	}
	pkt_list.push_back(curr);
	video_pkt_count++;
}

bool VideoStream::validate_pid(int pid)
{
	if((pid == mpeg1video) ||
		(pid == mpeg2video) ||
		(pid == mpeg4video) ||
		(pid == h264video))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void VideoStream::print_stats()
{
	//log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "Video Frame Stats");

	for(auto it = pkt_list.begin(), ite = pkt_list.end(); it != ite; it++)
	{
		if((*it)->PUSI_flag)
		{
			std::stringstream ss;
			for(int i = 0; i < (*it)->detected_slice_type_count; i++)
				ss << (*it)->slice_type[i].second << " ";
			log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "Video pkt %d offset %d DTS %llu Duration %d numslice %d %s", (*it)->pkt_count, (*it)->byte_offset, (*it)->dts, (*it)->duration_dts_ms, (*it)->detected_slice_type_count, ss.str().c_str());
		}
	}
}

std::list<VideoPktInfo *> &VideoStream::get_pkt_info()
{
	return pkt_list;
}

VideoPktInfo::VideoPktInfo(TsPacket *ts)
{
	pts = ts->get_PTS();
	dts = ts->get_DTS();
	byte_offset = ts->get_start_offset();
	PUSI_flag = ts->get_PUSI_flag();
	pkt_count = ts->get_count();
	detected_slice_type_count = 0;
	if(PUSI_flag)
		detect_slice_type(ts);
}



VideoPktInfo::~VideoPktInfo()
{
}


void VideoPktInfo::set_prev(VideoPktInfo *prev)
{
	duration_pts_ms = 0;
	duration_dts_ms = 0;
	if(prev != NULL)
	{
		duration_pts_ms = (unsigned int)((pts - prev->pts)/TS_TIMESCALE_MILLISEC);
		duration_dts_ms = (unsigned int)((dts - prev->dts)/TS_TIMESCALE_MILLISEC);
	}
}

#define PROCESS_VAL(p) case(p): str = #p; break;
const char * VideoPktInfo::convert_slice_type_string(H264_VIDEO_SLICE_TYPE type)
{
	const char *str = 0;
	switch(type)
	{
		PROCESS_VAL(unspecified)
		PROCESS_VAL(non_idr)
		PROCESS_VAL(data_partition_a)
		PROCESS_VAL(data_partition_b)
		PROCESS_VAL(data_partition_c)
		PROCESS_VAL(idr)
		PROCESS_VAL(sei)
		PROCESS_VAL(sps)
		PROCESS_VAL(pps)
		PROCESS_VAL(au_delimiter)
		PROCESS_VAL(eosequence)
		PROCESS_VAL(eostream)
		PROCESS_VAL(filler)
		PROCESS_VAL(sps_extension)
		PROCESS_VAL(aux_picture_without_partition)
	}
	return str;
}
#undef PROCESS_VAL


void VideoPktInfo::detect_slice_type(TsPacket *ts)
{
	std::vector<unsigned char> data_bytes = ts->get_pes_packet()->get_data_bytes();
	H264_VIDEO_SLICE_TYPE tmp;
	const char *str;
	for(int i = 0; i < DATA_BYTES_STORAGE - 4; i++)
	{
		unsigned int checkword1 = ((data_bytes[i] << 16) | (data_bytes[i+1] << 8) | data_bytes[i+2]);
		unsigned int checkword2 = ((checkword1 << 8) | data_bytes[i+3]);
		if(checkword1 == (unsigned int)H264_START_CODE1)
		{
			tmp = (H264_VIDEO_SLICE_TYPE)(data_bytes[i+3] & 0x1f);
			str = convert_slice_type_string(tmp);
			slice_type.push_back(std::pair<H264_VIDEO_SLICE_TYPE, const char *>(tmp, str));
			detected_slice_type_count++;
		}
		else if(checkword2 == (unsigned int)H264_START_CODE2)
		{
			tmp = (H264_VIDEO_SLICE_TYPE)(data_bytes[i+4] & 0x1f);
			str = convert_slice_type_string(tmp);
			slice_type.push_back(std::pair<H264_VIDEO_SLICE_TYPE, const char *>(tmp, str));
			detected_slice_type_count++;
			i++;
		}
	}
}


