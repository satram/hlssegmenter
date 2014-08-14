/*
 * MediaPlaylist.h
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#ifndef MEDIAPLAYLIST_H_
#define MEDIAPLAYLIST_H_

#include "segmenterCommon.h"

class MediaPlaylist : public PlaylistInterface
{
public:
	MediaPlaylist();
	virtual ~MediaPlaylist();
	void add_header(ConfigParams & config);
	void add_header(variant_stream_info &stream_info);
	void add_node(IndexBase *index, VariantPlaylist *variant_playlist);
	void remove_node(IndexBase *idx);
	void add_footer();
	void finalize_playlist();
};

#endif /* MEDIAPLAYLIST_H_ */
