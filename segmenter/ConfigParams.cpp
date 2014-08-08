/*
 * ConfigParams.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "ConfigParams.h"

ConfigParams::ConfigParams()
{
}

ConfigParams::~ConfigParams()
{
	for(auto it = variant_streams.begin(), ite = variant_streams.end(); it != ite; it++)
	{
		variant_streams.erase(it);
		delete (it->mediaUrl);
		delete (it->iframeUrl);
		break;
	}
}

void ConfigParams::add_variant(variant_stream_info & var)
{
	variant_streams.push_back(var);
}

void ConfigParams::remove_variant(std::string id)
{
	for(auto it = variant_streams.begin(), ite = variant_streams.end(); it != ite; it++)
	{
		if(it->id == id)
		{
			variant_streams.erase(it);
			delete (it->mediaUrl);
			delete (it->iframeUrl);
			break;
		}
	}
}




