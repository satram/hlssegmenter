/*
 * MediaPlaylist.h
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#ifndef MEDIAPLAYLIST_H_
#define MEDIAPLAYLIST_H_

#include "segmenterCommon.h"
#include "PlaylistInterface.h"


class MediaPlaylist : public PlaylistInterface
{
	unsigned int sequence_number;
public:
	MediaPlaylist();
	virtual ~MediaPlaylist();
	void add_header(ConfigParams & config);
	void add_header(variant_stream_info &stream_info);
	void update_node(ChunkIndex *index, VariantPlaylist *variant_playlist, bool addition);
	void add_footer();
	void finalize_playlist();
};

#endif /* MEDIAPLAYLIST_H_ */
