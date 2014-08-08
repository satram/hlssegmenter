/*
 * VideoStream.h
 *
 *  Created on: Jul 17, 2014
 *      Author: satram
 */

#ifndef VIDEOSTREAM_H_
#define VIDEOSTREAM_H_

#include "Common.h"

#define H264_START_CODE1 (0x000001)
#define H264_START_CODE2 (0x00000001)

enum VIDEO_STREAM_TYPE
{
	mpeg1video = 0x1,
	mpeg2video = 0x2,
	mpeg4video = 0x10,
	h264video = 0x1b
};

enum H264_VIDEO_SLICE_TYPE
{
	unspecified = 0,
	non_idr = 1,
	data_partition_a,
	data_partition_b,
	data_partition_c,
	idr = 5,
	sei,
	sps,
	pps,
	au_delimiter = 9,
	eosequence,
	eostream,
	filler = 12,
	sps_extension,
	aux_picture_without_partition = 19
};

class VideoPktInfo
{
	bool PUSI_flag;
	long long pts;
	long long dts;
	unsigned int duration_pts_ms;
	unsigned int duration_dts_ms;
	int byte_offset;
	int pkt_count;

	int detected_slice_type_count;
	std::vector<std::pair<H264_VIDEO_SLICE_TYPE, const char *>> slice_type;
	const char * convert_slice_type_string(H264_VIDEO_SLICE_TYPE type);
	void detect_slice_type(TsPacket *ts);

public:
	VideoPktInfo(TsPacket *ts);
	~VideoPktInfo();
	void set_prev(VideoPktInfo *prev);
	friend class VideoStream;
	friend class Segmenter;
};



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
