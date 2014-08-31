cmake_minimum_required (VERSION 2.6)
project (mediatools)

set (TS_SRC AudioStream.cpp)
LIST(APPEND TS_SRC Bitstream.cpp)
LIST(APPEND TS_SRC ParseAdaptationField.cpp)
LIST(APPEND TS_SRC ParsePESPacket.cpp)
LIST(APPEND TS_SRC ParseTsHeader.cpp)
LIST(APPEND TS_SRC ParseTsStream.cpp)
LIST(APPEND TS_SRC PatParse.cpp)
LIST(APPEND TS_SRC PmtParse.cpp)
LIST(APPEND TS_SRC Profiler.cpp)
LIST(APPEND TS_SRC SectionHeader.cpp)
LIST(APPEND TS_SRC TsPacket.cpp)
LIST(APPEND TS_SRC VideoStream.cpp)


add_library(mediatools SHARED ${TS_SRC})