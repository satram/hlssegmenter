/*
 * segmenterCommon.h
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#ifndef SEGMENTERCOMMON_H_
#define SEGMENTERCOMMON_H_

#include <cstdio>
#include <iostream>
#include <string>
#include <list>
#include <exception>
#include <map>
#include <algorithm>
#include <thread>
#include <sstream>

#include "log4c.h"


#include <ParseTsStream.h>
#include <m3u8/Name.h>
#include <m3u8/Property.h>
#include <m3u8/Tag.h>
#include <m3u8/Section.h>
#include <m3u8/Playlist.h>


enum hls_playlist_type
{
	LIVE,
	EVENT,
	VOD
};
class HlsConfigParams;
struct variant_stream_info;
class VariantPlaylist;
class PlaylistInterface;
class IFramePlaylist;
class MasterPlaylist;
class MediaPlaylist;
class HlsPlaylistGenerator;
class IndexBase;
class IFrameIndex;
class ChunkIndex;
class Segmenter;

#include "HlsConfigParams.h"
#include "Segmenter.h"

#endif /* SEGMENTERCOMMON_H_ */
