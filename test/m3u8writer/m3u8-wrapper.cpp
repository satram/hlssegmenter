//============================================================================
// Name        : m3u8-wrapper.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "m3u8/Common.h"
#include "UnitTest.h"


int main(int argc, char *argv[])
{
	UnitTest ut;
	ut.generate_master_playlist();
	ut.simple_media_playlist();
	ut.playlist_with_encrypted_mediasegments();
	ut.iframe_master_playlist();
	ut.live_media_playlist();
	ut.live_media_playlist_1();
	return 0;
}
