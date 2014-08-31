cmake_minimum_required (VERSION 2.6)
project (tsparser)


include_directories(../../mediatools ../../segmenter)
add_executable(tsparser TsParserTestMain.cpp)

target_link_libraries(tsparser mediatools)
target_link_libraries(tsparser log4c)