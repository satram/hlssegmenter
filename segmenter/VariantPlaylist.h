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
    std::string transcoded_output_url;
    std::string transcoded_output_path;
    std::string transcoded_output_filename;
    std::string ready_for_streaming_filename;
    std::string media_playlist_filename;
    std::string iframe_playlist_filename;
    MediaPlaylist *mediaUrl;
    IFramePlaylist *iframeUrl;
    std::string leaf_id;

    std::ofstream mediafile;

public:
    VariantPlaylist(HlsConfigParams & config, variant_stream_info & var);
    virtual ~VariantPlaylist();
    void publish_playlist();
    void update_playlist(IndexBase *index, bool addition);

    void add_header(HlsConfigParams & config, variant_stream_info & var);

    void publish_media(const char *inp_buffer, int bufsize);
    void finalize_playlist();

    friend class MediaPlaylist;
	friend class IFramePlaylist;

};

#endif /* VARIANTPLAYLIST_H_ */
