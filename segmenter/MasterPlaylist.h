/*
 * MasterPlaylist.h
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#ifndef MASTERPLAYLIST_H_
#define MASTERPLAYLIST_H_

#include "segmenterCommon.h"

class MasterPlaylist : public PlaylistInterface
{
	Playlist playlist;
	std::string playlist_path;
	std::string playlist_name;

public:
	MasterPlaylist();
	virtual ~MasterPlaylist();
	void set_url(std::string &path, std::string &filename);
	void add_header(ConfigParams & config);
	void add_header(variant_stream_info &stream_info);
	void add_node(IFrameIndex *index, VariantPlaylist *variant_playlist);
	void remove_node();
	void publish_playlist();
	void add_footer();
};

#endif /* MASTERPLAYLIST_H_ */
