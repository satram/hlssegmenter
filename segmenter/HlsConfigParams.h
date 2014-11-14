/*
 * ConfigParams.h
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#ifndef CONFIGPARAMS_H_
#define CONFIGPARAMS_H_

#include "segmenterCommon.h"



struct video_codec_info
{
	VIDEO_STREAM_TYPE codec;
	std::string profile;
	double level;
	std::string resolution;
};

struct audio_codec_info
{
	AUDIO_STREAM_TYPE codec;
	std::string subtype;
};



struct variant_stream_info
{
	std::string id;
	int bandwidth;
	bool generate_iframe_url;
	video_codec_info vid;
	audio_codec_info aud;
};


class HlsConfigParams {
	std::list<variant_stream_info> variant_streams;

public:
	//common parameters across variants streams
	std::string leaf_id;
	std::string web_server_url;
	std::string output_folder;

	hls_playlist_type playlist_type;
	unsigned int segment_duration_ms;
	unsigned int sliding_window_duration_ms;

	HlsConfigParams();
	virtual ~HlsConfigParams();
	void add_variant(variant_stream_info &var);
	void remove_variant(std::string id);
	const char *convert_playlist_enum_to_string(hls_playlist_type type);

	friend class MasterPlaylist;
	friend class MediaPlaylist;
	friend class IFramePlaylist;
	friend class HlsPlaylistGenerator;
	friend class variants_playlist;

};

#endif /* CONFIGPARAMS_H_ */
