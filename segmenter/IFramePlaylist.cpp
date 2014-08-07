/*
 * IFramePlaylist.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "IFramePlaylist.h"

IFramePlaylist::IFramePlaylist() {
	// TODO Auto-generated constructor stub

}

IFramePlaylist::~IFramePlaylist() {
	// TODO Auto-generated destructor stub
}

void IFramePlaylist::publish_playlist()
{
	std::cout << "i-frame playlist" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	std::cout << iframe_playlist.marshall();
}



void IFramePlaylist::add_node()
{
}



void IFramePlaylist::add_header()
{
}



void IFramePlaylist::remove_node()
{
}


