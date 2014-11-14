/*
 * IndexBase.h
 *
 *  Created on: Aug 13, 2014
 *      Author: satram
 */

#ifndef INDEXBASE_H_
#define INDEXBASE_H_

#include <utility>
#include "PlaylistInterface.h"

class IndexBase
{
protected:
	std::pair<bool,bool> add_to_playlist; //pair of do and done
	unsigned int duration;
	long long start_offset;
	long long size;
	bool purge;

public:
	IndexBase();
	virtual ~IndexBase();
	virtual void dispatch(PlaylistInterface *playlist, VariantPlaylist *var, bool addition)=0;
	unsigned int get_duration()
	{
		return duration;
	};
	bool get_purge_status()
	{
		return purge;
	};
	void set_purge_status(bool new_purge_status)
	{
		purge = new_purge_status;
	};
	std::pair<bool, bool>& get_add_to_playlist()
	{
		return add_to_playlist;
	};
};



#endif /* INDEXBASE_H_ */
