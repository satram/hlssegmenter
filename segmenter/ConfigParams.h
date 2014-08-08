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

enum hls_playlist_type
{
	live,
	event,
	vod
};

struct variant_stream_info
{
	std::string id;
	int bandwidth;
	bool generate_iframe_url;
	video_codec_info vid;
	audio_codec_info aud;

	//updated based on global config params
	std::string transcoded_output_url;
	std::string transcoded_output_path;
	std::string transcoded_output_filename;
	std::string media_playlist_filename;
	std::string iframe_playlist_filename;

	MediaPlaylist *mediaUrl;
	IFramePlaylist *iframeUrl;
};


class ConfigParams {
	std::list<variant_stream_info> variant_streams;

public:
	//common parameters across variants streams
	std::string web_server_url;
	std::string output_folder;
	hls_playlist_type playlist_type;
	double segment_duration;
	int sliding_window_duration;

	ConfigParams();
	virtual ~ConfigParams();
	void add_variant(variant_stream_info &var);
	void remove_variant(std::string id);

	friend class MasterPlaylist;
	friend class MediaPlaylist;
	friend class IFramePlaylist;
	friend class HlsPlaylistGenerator;

};

#endif /* CONFIGPARAMS_H_ */
