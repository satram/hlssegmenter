/*
 * Profiler.h
 *
 *  Created on: Jul 30, 2014
 *      Author: satram
 */

#ifndef PROFILER_H_
#define PROFILER_H_

#include "mt_common.h"

class Profiler
{
	std::string name;
	int previous_ts;
	int difftime(int firstts, int secondts);
	int gettime();
	int get_elapsed_time();

	unsigned int min_duration;
	unsigned int max_duration;
	unsigned int samplecount;
	unsigned int avg_duration;
	long long total_duration;

public:
	Profiler(){};
	Profiler(const std::string &str);
	virtual ~Profiler();
	void record_elapsed_time();
	void print_stats();
	void start_timer();
};

#endif /* PROFILER_H_ */
