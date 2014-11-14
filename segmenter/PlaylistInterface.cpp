/*
 * PlaylistInterface.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: satram
 */

#include <stdio.h>
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
	std::string tmp_filename = playlist_url + "_tmp";
	file.open(tmp_filename, std::ofstream::out);
	if(file.is_open())
	{
		file << playlist.marshall();
		file.close();
		rename(tmp_filename.c_str(), playlist_url.c_str());
	}
	else
	{
		std::ostringstream oss;
		oss << "Unable to open file " << playlist_url;
		throw std::runtime_error(oss.str());
	}
}

