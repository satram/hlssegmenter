cmake_minimum_required (VERSION 2.6)
project (segmenter)

set (SEGMENTER_SRC ChunkIndex.cpp)
LIST(APPEND SEGMENTER_SRC ConfigParams.cpp)
LIST(APPEND SEGMENTER_SRC HlsPlaylistGenerator.cpp)
LIST(APPEND SEGMENTER_SRC IFrameIndex.cpp)
LIST(APPEND SEGMENTER_SRC IFramePlaylist.cpp)
LIST(APPEND SEGMENTER_SRC IndexBase.cpp)
LIST(APPEND SEGMENTER_SRC MasterPlaylist.cpp)
LIST(APPEND SEGMENTER_SRC MediaPlaylist.cpp)
LIST(APPEND SEGMENTER_SRC PlaylistInterface.cpp)
LIST(APPEND SEGMENTER_SRC Segmenter.cpp)
LIST(APPEND SEGMENTER_SRC VariantPlaylist.cpp)

include_directories(../mediatools .)


add_library(segmenter SHARED ${SEGMENTER_SRC})