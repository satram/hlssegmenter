/*
 * Profiler.h
 *
 *  Created on: Jul 30, 2014
 *      Author: satram
 */

#ifndef PROFILER_H_
#define PROFILER_H_

#include "mt_common.h"
#include <chrono>
#include <limits>

class Profiler
{
	std::string name;
	std::chrono::time_point<std::chrono::system_clock> begin;
	std::chrono::time_point<std::chrono::system_clock> end;

	double min_duration;
	double max_duration;
	unsigned int samplecount;
	double avg_duration;
	std::chrono::duration<double, std::micro> total_duration;

public:
	Profiler(){};
	Profiler(const std::string &str);
	virtual ~Profiler();
	void stop();
	void print_stats();
	void start();
};

#endif /* PROFILER_H_ */
