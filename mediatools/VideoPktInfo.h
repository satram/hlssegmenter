/*
 * VdeoPktInfo.h
 *
 *  Created on: Sep 1, 2014
 *      Author: satram
 */

#ifndef VDEOPKTINFO_H_
#define VDEOPKTINFO_H_
#define H264_START_CODE1 (0x000001)
#define H264_START_CODE2 (0x00000001)


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


#endif /* VDEOPKTINFO_H_ */
