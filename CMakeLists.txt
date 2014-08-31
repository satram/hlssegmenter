cmake_minimum_required(VERSION 2.8)

set(CMAKE_SYSTEM_NAME Linux)

link_directories(/usr/local/lib)

set(CMAKE_CXX_FLAGS "-O0 -g3 -Wall -fPIC -std=c++0x -D_GLIBCXX_USE_NANOSLEEP")

add_subdirectory(mediatools)
add_subdirectory(segmenter)

add_subdirectory(test/hlssegmenter)
add_subdirectory(test/m3u8writer)
add_subdirectory(test/tsparser)

