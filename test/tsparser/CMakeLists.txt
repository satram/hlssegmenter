cmake_minimum_required (VERSION 2.6)
project (tsparser)


include_directories(../../mediatools ../../segmenter ../../transcode)
add_executable(tsparser TsParserTestMain.cpp)

link_directories(/usr/local/lib)

target_link_libraries(tsparser mediatools)
target_link_libraries(tsparser log4c)