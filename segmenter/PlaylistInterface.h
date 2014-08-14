/*
 * PlaylistInterface.h
 *
 *  Created on: Aug 7, 2014
 *      Author: satram
 */

#ifndef PLAYLISTINTERFACE_H_
#define PLAYLISTINTERFACE_H_

#include "segmenterCommon.h"

class PlaylistInterface {
protected:
	std::string playlist_path;
	std::string playlist_name;
	std::string playlist_url;

	Playlist playlist;

public:
	//PlaylistInterface();
	//virtual ~PlaylistInterface();
	void set_url(std::string &path, std::string &filename);
	void publish_playlist();
	virtual void add_header(ConfigParams & config){throw std::runtime_error("this is not defined in base");};
	virtual void add_header(variant_stream_info &stream_info){throw std::runtime_error("this is not defined in base");};
	virtual void add_node(IndexBase *index, VariantPlaylist *variant_playlist){throw std::runtime_error("this is not defined in base");};
	virtual void remove_node(IndexBase *idx){throw std::runtime_error("this is not defined in base");};
	virtual void add_footer(){throw std::runtime_error("this is not defined in base");};
	virtual void finalize_playlist(){throw std::runtime_error("this is not defined in base");};
};


#endif /* PLAYLISTINTERFACE_H_ */
