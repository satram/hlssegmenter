/*
 * ConfigParams.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "HlsConfigParams.h"

HlsConfigParams::HlsConfigParams()
{
}

HlsConfigParams::~HlsConfigParams()
{
	for(auto it = variant_streams.begin(), ite = variant_streams.end(); it != ite; it++)
	{
		it = variant_streams.erase(it);
	}
}

void HlsConfigParams::add_variant(variant_stream_info & var)
{
	variant_streams.push_back(var);
}

void HlsConfigParams::remove_variant(std::string id)
{
	for(auto it = variant_streams.begin(), ite = variant_streams.end(); it != ite; it++)
	{
		if(it->id == id)
		{
			variant_streams.erase(it);
			break;
		}
	}
}

#define PROCESS_VAL(n) case(n): str = #n; break;
const char *HlsConfigParams::convert_playlist_enum_to_string(hls_playlist_type type)
{
	const char *str;
	switch(type)
	{
		PROCESS_VAL(EVENT)
		PROCESS_VAL(LIVE)
		PROCESS_VAL(VOD)
	}
	return str;
}
#undef PROCESS_VAL
