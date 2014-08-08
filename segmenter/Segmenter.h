/*
 * Segmenter.h
 *
 *  Created on: Aug 7, 2014
 *      Author: satram
 */

#ifndef SEGMENTER_H_
#define SEGMENTER_H_

#include "segmenterCommon.h"

class decision_flags
{
	bool idr_identified;
	bool idr_size_calculated;
	bool update_iframe_playlist;
	bool chunk_start;
	bool update_media_playlist;
public:
	decision_flags()
	{
		idr_identified = false;
		idr_size_calculated = false;
		update_iframe_playlist = false;
		chunk_start = false;
		update_media_playlist = false;
	}
	~decision_flags() {};
	friend class idr_info;
};


class idr_info
{
	int total_pkt_count;
	long long total_byte_offset;
	long long dts;
	int idr_size;
	int chunk_size;
	double duration_from_last_idr;
	double duration_from_chunk_start;

	decision_flags flags;
public:
	idr_info(int count, long long timestamp, long long byte_offset)
	{
		total_pkt_count = count;
		dts = timestamp;
		total_byte_offset = byte_offset;
		flags.idr_identified = true;
		idr_size = 0;
		chunk_size = 0;
		duration_from_last_idr = 0;
	};
	~idr_info(){};

	void update_idr_info(int count, long long timestamp, long long byte_offset)
	{
		if(flags.idr_identified)
		{
			if(!flags.idr_size_calculated)
			{
				idr_size = byte_offset - total_byte_offset;
				flags.idr_size_calculated = true;
			}
			duration_from_last_idr += timestamp;
		}
	}

	void finalize_idr_info(int count, long long timestamp, long long byte_offset)
	{
		if(flags.idr_identified)
		{
			duration_from_last_idr += timestamp;
			flags.update_iframe_playlist = true;
		}
	}


};


class Segmenter {

	std::list<idr_info *> index;
	int ts_packet_count;
	long long byte_offset;

	ParseTsStream input_ts_stream;
	HlsPlaylistGenerator* hls_playlist;
    void create_index_table();

public:
	Segmenter(ConfigParams &config);
	virtual ~Segmenter();

	void parse_ts_packets(const char *inp_buffer, int bufsize);
};

#endif /* SEGMENTER_H_ */
