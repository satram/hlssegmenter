/*
 * UnitTest.h
 *
 *  Created on: Jul 31, 2014
 *      Author: satram
 */

#ifndef UNITTEST_H_
#define UNITTEST_H_

#include "m3u8/Common.h"

class UnitTest {
	void add_node_to_playlist(int sequencenum, double duration, Playlist &tmp);
	void add_node_playlist_byterange(double duration, int length, int offset, Playlist &live);
public:
	UnitTest();
	virtual ~UnitTest();
	int generate_master_playlist();
	int  file_parsing(char *argv[]);
	int  simple_media_playlist();
	int  live_media_playlist();
	int playlist_with_encrypted_mediasegments();
	int iframe_master_playlist();
	int live_media_playlist_1();


};

#endif /* UNITTEST_H_ */
