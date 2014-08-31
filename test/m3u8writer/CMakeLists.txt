cmake_minimum_required (VERSION 2.6)
project (m3u8writer)


include_directories(../../segmenter ../../mediatools)
add_executable(m3u8writer m3u8-wrapper.cpp  UnitTest.cpp)

