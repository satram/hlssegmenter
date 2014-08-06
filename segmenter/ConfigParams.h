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
	int profile;
	int level;
};

struct audio_codec_info
{
	AUDIO_STREAM_TYPE codec;
};

struct variant_list_info
{
	std::string id;
	int bandwidth;
	bool generate_iframe_url;
	video_codec_info vid;
	audio_codec_info aud;
};


class ConfigParams {

	int num_variant_streams;
	std::list<variant_list_info> variant_streams;

public:
	ConfigParams();
	virtual ~ConfigParams();
};

#endif /* CONFIGPARAMS_H_ */
