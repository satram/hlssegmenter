/*
 * Profiler.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: satram
 */

#include "Profiler.h"

Profiler::Profiler(const std::string &str)
{
	name = str;
	min_duration = std::numeric_limits<double>::max();
	max_duration = std::numeric_limits<double>::min();
	avg_duration = 0;
	samplecount = 0;
	total_duration = std::chrono::duration<double, std::micro>::zero();
	begin = end = std::chrono::system_clock::now();
}

Profiler::~Profiler() {
	// TODO Auto-generated destructor stub
}

void Profiler::print_stats()
{
#if defined(PROFILING_SUPPORT)
	//printf("%s Profiler: SampleCnt %d Average(us) %d Max(us) %d Min(us) %d Total(us) %llu\n", name.c_str(), samplecount, avg_duration, max_duration, min_duration, total_duration);
	std::ostringstream oss;
	oss << name;
	oss << "\t SampleCnt " << std::setw(10) << samplecount;
	oss << "\t Avg(us) " << std::setw(10) << avg_duration;
	oss << "\t min(us) " << std::setw(10) << min_duration;
	oss << "\t max(us) " << std::setw(10) << max_duration;
	oss << "\t Total(ms) " << std::setw(10) << std::chrono::duration<double, std::milli>(total_duration).count() << std::endl;
	std::cout << oss.str();
#endif
}

void Profiler::stop()
{
#if defined(PROFILING_SUPPORT)
	end = std::chrono::system_clock::now();
	samplecount++;
	std::chrono::duration<double, std::micro> elapsed = end - begin;
	double diff = elapsed.count();
	begin = end;
	if(diff < min_duration)
		min_duration = diff;
	if(diff > max_duration)
		max_duration = diff;
	avg_duration = ((avg_duration * (samplecount-1)) + diff) / samplecount;
	total_duration += elapsed;
#endif
}

void Profiler::start()
{
#if defined(PROFILING_SUPPORT)
	begin = std::chrono::system_clock::now();
#endif
}


