cmake_minimum_required (VERSION 2.6)
project (hlssegmenter)


include_directories(../../mediatools ../../segmenter ../../transcode)

add_executable(hlssegmenter testMain.cpp)

target_link_libraries(hlssegmenter segmenter)
target_link_libraries(hlssegmenter mediatools)
target_link_libraries(hlssegmenter log4c)