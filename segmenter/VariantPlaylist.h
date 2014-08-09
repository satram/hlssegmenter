/*
 * VariantPlaylist.h
 *
 *  Created on: Aug 8, 2014
 *      Author: satram
 */

#ifndef VARIANTPLAYLIST_H_
#define VARIANTPLAYLIST_H_

#include "segmenterCommon.h"

class VariantPlaylist {
	//updated based on global config params
	std::string transcoded_output_url;
	std::string transcoded_output_path;
	std::string transcoded_output_filename;
	std::string media_playlist_filename;
	std::string iframe_playlist_filename;

	MediaPlaylist *mediaUrl;
	IFramePlaylist *iframeUrl;
public:
	VariantPlaylist(ConfigParams &config, variant_stream_info &var);
	virtual ~VariantPlaylist();
	void publish_playlist();
};

#endif /* VARIANTPLAYLIST_H_ */
