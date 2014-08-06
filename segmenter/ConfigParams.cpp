/*
 * ConfigParams.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "ConfigParams.h"

ConfigParams::ConfigParams() {
	num_variant_streams = 0;
}

ConfigParams::~ConfigParams() {
	// TODO Auto-generated destructor stub
}

void ConfigParams::add_variant(variant_stream_info & var)
{
	num_variant_streams++;
	variant_streams.push_back(var);

}


