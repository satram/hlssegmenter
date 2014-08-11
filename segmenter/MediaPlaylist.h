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

	Playlist playlist;
	std::string playlist_path;
	std::string playlist_name;

public:
	MediaPlaylist();
	virtual ~MediaPlaylist();
	void set_url(std::string &path, std::string &filename);
	void add_header(ConfigParams & config);
	void add_header(variant_stream_info &stream_info);
	void add_node(IFrameIndex *index, VariantPlaylist *variant_playlist);
	void remove_node();
	void publish_playlist();
	void add_footer();
};

#endif /* MEDIAPLAYLIST_H_ */
