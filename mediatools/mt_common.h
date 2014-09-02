/*
 * mt_common.h
 *
 *  Created on: Sep 1, 2014
 *      Author: satram
 */

#ifndef MT_COMMON_H_
#define MT_COMMON_H_

#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <assert.h>
#include <exception>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <map>
#include <list>
#include <stdio.h>
#include <sys/time.h>

#include "log4c.h"

class Bitstream;
class TsPacket;
class SectionHeader;
class PatParse;
class PmtParse;
class VideoStream;
class AudioStream;
class ParseAdaptationField;
class ParsePESPacket;
class ParseTsHeader;
class Profiler;
class VideoPktInfo;
class Profiler;

#define BYTE_SIZE 			(8)
#define NUM_BYTES_IN_WORD 	(4)
#define WORD_SIZE 			(NUM_BYTES_IN_WORD * BYTE_SIZE)
#define TS_PKT_SIZE_BYTES 	(188)
#define LENGTH_VAR_BYTES	(1)
#define MAX_PID				(0x1fff)
#define TS_TIMESCALE_MILLISEC		(90)
#define TS_TIMESCALE_SECONDS		(90000)
#define DATA_BYTES_STORAGE	(100)

enum AUDIO_STREAM_TYPE
{
	mpeg1audio = 0x3,
	mpeg2audio = 0x4,
	mpeg2audio_adts = 0xf,
	mpeg4audio_latm = 0x11
};

enum VIDEO_STREAM_TYPE
{
	mpeg1video = 0x1,
	mpeg2video = 0x2,
	mpeg4video = 0x10,
	h264video = 0x1b
};

#endif /* MT_COMMON_H_ */
