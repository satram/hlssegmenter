/*
 * Common.h
 *
 *  Created on: Jul 2, 2014
 *      Author: satram
 */

#ifndef COMMON_H_
#define COMMON_H_

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

#define BYTE_SIZE 			(8)
#define NUM_BYTES_IN_WORD 	(4)
#define WORD_SIZE 			(NUM_BYTES_IN_WORD * BYTE_SIZE)
#define TS_PKT_SIZE_BYTES 	(188)
#define LENGTH_VAR_BYTES	(1)
#define MAX_PID				(0x1fff)
#define TS_TIMESCALE_MILLISEC		(90)
#define TS_TIMESCALE_SECONDS		(90000)
#define DATA_BYTES_STORAGE	(100)




#include "Bitstream.h"
#include "SectionHeader.h"
#include "ParseAdaptationField.h"
#include "ParseTsHeader.h"
#include "PatParse.h"
#include "PmtParse.h"
#include "ParsePESPacket.h"
#include "ElementaryStream.h"
#include "VideoStream.h"
#include "AudioStream.h"
#include "TsPacket.h"
#include "Profiler.h"
//#include "ParseTsStream.h"






#endif /* COMMON_H_ */
