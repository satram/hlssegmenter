/*
 * PlaylistInterface.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: satram
 */

#include "PlaylistInterface.h"
#include "tools.h"

//PlaylistInterface::PlaylistInterface()
//{
//
//}

void PlaylistInterface::set_url(std::string &path, std::string &filename)
{
	//std::cout << " seturl " << std::endl;
	playlist_path = path;
	playlist_name = filename;
	playlist_url = playlist_path + "/" + playlist_name;
	mkpath(playlist_path.c_str(), 0777);
}

void PlaylistInterface::publish_playlist()
{
	//std::cout << " publishing playlist " << playlist_url << std::endl;
	std::ofstream file;
	file.open(playlist_url, std::ofstream::out);
	if(file.is_open())
	{
		file << playlist.marshall();
		file.close();
	}
	else
		throw std::runtime_error("Unable to open file");
}

