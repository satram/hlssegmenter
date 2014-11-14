/*
 * MasterPlaylist.h
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#ifndef MASTERPLAYLIST_H_
#define MASTERPLAYLIST_H_

#include "segmenterCommon.h"
#include "PlaylistInterface.h"

class MasterPlaylist : public PlaylistInterface
{
public:
	MasterPlaylist();
	virtual ~MasterPlaylist();
	void add_header(HlsConfigParams & config);
	void add_header(variant_stream_info &stream_info){};
	void update_node(IndexBase *index, VariantPlaylist *variant_playlist, bool addition){};
	void add_footer(){};
	void finalize_playlist(){};
};

#endif /* MASTERPLAYLIST_H_ */
