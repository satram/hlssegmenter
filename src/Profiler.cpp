/*
 * Profiler.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: satram
 */

#include "Profiler.h"

Profiler::Profiler(const std::string &str) {
	name = str;
	previous_ts = 0;
	min_duration = 0x7fffffff;
	max_duration = 0;
	avg_duration = 0;
	samplecount = 0;
	total_duration = 0;
}

Profiler::~Profiler() {
	// TODO Auto-generated destructor stub
}

int Profiler::difftime(int firstts, int secondts)
{
	int diff = firstts - secondts;
	return diff;
}

int Profiler::gettime()
{
	struct timeval tv;
	struct timezone tz;
	if(gettimeofday(&tv, &tz) == -1)
		return 0;
	else
	{
		int time_elapsed = tv.tv_sec * 1000000 + tv.tv_usec;
		return time_elapsed;
	}
}

int Profiler::get_elapsed_time()
{
	int current_ts = gettime();
	samplecount++;
	if(previous_ts == 0)
	{
		previous_ts = current_ts;
		return 0;
	}
	else
	{
		int diff = difftime(current_ts ,previous_ts);
		previous_ts = current_ts;
		return diff;
	}
}

void Profiler::print_stats()
{
	printf("%s Profiler: SampleCnt %d Average(us) %d Max(us) %d Min(us) %d Total(us) %llu\n", name.c_str(), samplecount, avg_duration, max_duration, min_duration, total_duration);
}



void Profiler::record_elapsed_time()
{
	unsigned int diff = get_elapsed_time();
	if(diff < min_duration)
		min_duration = diff;
	if(diff > max_duration)
		max_duration = diff;
	avg_duration = ((avg_duration * (samplecount-1)) + diff) / samplecount;
	total_duration += diff;
}

void Profiler::start_timer()
{
	previous_ts = gettime();
}


