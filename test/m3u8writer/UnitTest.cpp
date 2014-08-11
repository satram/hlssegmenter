/*
 * UnitTest.cpp
 *
 *  Created on: Jul 31, 2014
 *      Author: satram
 */

#include "UnitTest.h"

UnitTest::UnitTest() {
	// TODO Auto-generated constructor stub

}

UnitTest::~UnitTest() {
	// TODO Auto-generated destructor stub
}


int UnitTest::generate_master_playlist()
{
	std::cout << "sample master playlist generation" << std::endl;
	std::cout << "----------------------------------\n";

	Section header("header");
	header.add_tag("M3U");
	header.add_tag("VERSION", 3);
	std::cout << header.marshall();


	{
		Section node("n1");
		Tag t("STREAM-INF");
		t.add_property("PROGRAM-ID", 1);
		t.add_property("BANDWIDTH", 512000);
		t.add_property("RESOLUTION","1280x720");
		t.add_property("CODECS","\"avc1.42e00a,mp4a.40.2\"");
//		t.mod_property("BANDWIDTH", 48000);
//		t.mod_property("RESOLUTION","1920x1080");
//		t.delete_property("BANDWIDTH");
		node.add_tag(t);
		node.set_path("http://media.example.com/hlsserver/session20705");
		node.set_locator("stream1.m3u8");
		std::cout << node.marshall();
	}
	{
		Section node("n2");
		Tag t("STREAM-INF");
		t.add_property("PROGRAM-ID", 2);
		t.add_property("BANDWIDTH", 1024000);
		t.add_property("RESOLUTION","1280x720");
		t.add_property("CODECS","\"avc1.42e00a,mp4a.40.2\"");
		node.add_tag(t);
		node.set_path("http://media.example.com/hlsserver/session20705");
		node.set_locator("stream2.m3u8");
		std::cout << node.marshall();
	}
	{
		Section node("n3");
		Tag t("STREAM-INF");
		t.add_property("PROGRAM-ID", 3);
		t.add_property("BANDWIDTH", 128000);
		t.add_property("RESOLUTION","640x480");
		t.add_property("CODECS","\"mpeg4.42e00a,aac.40.2\"");
		node.add_tag(t);
		node.set_path("http://media.example.com/hlsserver/session20705");
		node.set_locator("stream3.m3u8");
		std::cout << node.marshall();
	}

	return 0;
}

int  UnitTest::file_parsing(char *argv[])
{
	std::ifstream infile(argv[1]);

	if(infile.is_open())
	{
		while(!infile.eof())
		{
			char inpline[256];
			infile.getline(inpline, 256);
			std::cout << inpline << std::endl;
		}
		infile.close();
	}
	//TODO not implemented yet
	return 0;
}

int  UnitTest::simple_media_playlist()
{
	std::cout << "simple media playlist" << std::endl;
	std::cout << "----------------------------------\n";

	Section header("header");
	header.add_tag("M3U");
	header.add_tag("VERSION", 3);
	header.add_tag("TARGETDURATION", 3220);
	std::cout << header.marshall();

	Section n1("n1");
	n1.add_tag("INF", 5219.2);
	n1.set_path("http://www.media.example.com");
	n1.set_locator("entire.ts");
	std::cout << n1.marshall();

	Section footer("footer");
	footer.add_tag("ENDLIST");
	std::cout << footer.marshall();

	return 0;

}

int  UnitTest::live_media_playlist()
{
	std::cout << "live media playlist " << std::endl;
	std::cout << "----------------------------------\n";

	Playlist live_playlist;

	try {
		Section header("header");
		header.add_tag("M3U");
		header.add_tag("VERSION", 3);
		header.add_tag("PLAYLIST-TYPE", "EVENT");
		header.add_tag("TARGETDURATION", 8);
		header.add_tag("MEDIA-SEQUENCE", 0);
		live_playlist.add_section(header);

		std::cout << live_playlist.marshall();


		Section tmp1 = live_playlist.get_section("header");
		tmp1.modify_tag("MEDIA-SEQUENCE", 2680);
		live_playlist.modify_section(tmp1);


		Section n1("n1");
		n1.add_tag("INF", 7.975);
		n1.set_path("http://www.media.example.com");
		n1.set_locator("filesequence2680.ts");
		live_playlist.add_section(n1);

		Section n2("n2");
		n2.add_tag("INF", 7.941);
		n2.set_path("http://www.media.example.com");
		n2.set_locator("filesequence2681.ts");
		live_playlist.add_section(n2);

		Section n3("n3");
		n3.add_tag("INF", 7.975);
		n3.set_path("http://www.media.example.com");
		n3.set_locator("filesequence2682.ts");
		live_playlist.add_section(n3);

		std::cout << live_playlist.marshall();

		std::cout << "live media playlist - modify " << std::endl;
		std::cout << "----------------------------------\n";

		//delete a section
		live_playlist.delete_section("n1");

		//modify a tag in a section
		Section tmp = live_playlist.get_section("header");
		tmp.modify_tag("MEDIA-SEQUENCE", 2681);
		live_playlist.modify_section(tmp);

		//add a section
		Section n4("n4");
		n4.add_tag("INF", 7.465);
		n4.set_path("http://www.media.example.com");
		n4.set_locator("filesequence2683.ts");
		live_playlist.add_section(n4);

	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}



	std::cout << live_playlist.marshall();

	return 0;
}

void UnitTest::add_node_to_playlist(int sequencenum, double duration, Playlist &sample_playlist)
{
	std::ostringstream oss;
	oss << "filesequence-" << sequencenum;

	Section node(oss.str());
	node.add_tag("INF", duration);
	node.set_path("http://media.example.com/");
	oss << ".ts";
	node.set_locator(oss.str().c_str());
	sample_playlist.add_section(node);
	return;
}

int UnitTest::playlist_with_encrypted_mediasegments()
{
	std::cout << "playlist_with_encrypted_mediasegments" << std::endl;
	std::cout << "---------------------------------\n";

	Playlist sample_playlist;

	Section header("header");
	header.add_tag("M3U");
	header.add_tag("VERSION", 3);
	header.add_tag("MEDIA-SEQUENCE", 7994);
	header.add_tag("TARGETDURATION", 15);
	sample_playlist.add_section(header);

	Section key1("key1");
	key1.add_tag("KEY","METHOD", "AES");
	sample_playlist.add_section(key1);

	add_node_to_playlist(52, 2.833, sample_playlist);
	add_node_to_playlist(53, 15, sample_playlist);
	add_node_to_playlist(54, 13.333, sample_playlist);

	sample_playlist.add_section(key1);

	add_node_to_playlist(55, 5.833, sample_playlist);
	add_node_to_playlist(56, 14, sample_playlist);
	add_node_to_playlist(57, 11.333, sample_playlist);

	std::cout << sample_playlist.marshall();

	return 0;


}

int UnitTest::iframe_master_playlist()
{

	std::cout << "master playlist with i-frames list" << std::endl;
	std::cout << "---------------------------------\n";

	Playlist sample_playlist;

	Section header("header");
	header.add_tag("M3U");
	header.add_tag("VERSION", 4);
	sample_playlist.add_section(header);

	{
		Section node("n1");
		Tag t("STREAM-INF");
		t.add_property("BANDWIDTH", 512000);
		t.add_property("RESOLUTION","1280x720");
		t.add_property("CODECS","\"avc1.42001f,mp4a.40.2\"");
		node.add_tag(t);
		node.set_path("http://192.168.1.254:8080/hlsserver/");
		node.set_locator("media.m3u8");
		sample_playlist.add_section(node);
	}

	{
		Section node("n1");
		Tag t("I-FRAME-STREAM-INF");
		t.add_property("BANDWIDTH", 512000);
		t.add_property("RESOLUTION","1280x720");
		t.add_property("CODECS","\"avc1.42001f,mp4a.40.2\"");
		t.add_property("URI","http://192.168.1.254:8080/hlsserver/iframe.m3u8");
		node.add_tag(t);
		sample_playlist.add_section(node);
	}


	std::cout << sample_playlist.marshall();

	return 0;
}

void UnitTest::add_node_playlist_byterange(double duration, int length, int offset, Playlist &sample_playlist)
{
	static int count = 0;

	std::ostringstream oss;
	oss << "trans-" << count;

	Section node(oss.str());
	node.add_tag("INF", duration);
	oss.str("");
	oss << length << "@" << offset;
	node.add_tag("BYTERANGE", oss.str());
	node.set_path("http://192.168.1.254:8080/hlsserver");
	node.set_locator("transcoded-output.ts");
	sample_playlist.add_section(node);

	count++;
	return;
}

int UnitTest::live_media_playlist_1()
{
	std::cout << "media playlist EVENT" << std::endl;
	std::cout << "---------------------------------\n";

	Playlist sample_playlist;

	Section header("header");
	header.add_tag("M3U");
	header.add_tag("VERSION", 3);
	header.add_tag("PLAYLIST-TYPE", "EVENT");
	header.add_tag("TARGET-DURATION", 3);
	header.add_tag("MEDIA-SEQUENCE", 0);
	sample_playlist.add_section(header);

	std::cout << sample_playlist.marshall();


	add_node_playlist_byterange(2.75, 54764, 0, sample_playlist);
	add_node_playlist_byterange(3, 45000, 56000, sample_playlist);
	add_node_playlist_byterange(2.95, 50000, 110000, sample_playlist);
	add_node_playlist_byterange(2.85, 54700,16000, sample_playlist);
	add_node_playlist_byterange(3, 54764, 210000, sample_playlist);

	std::cout << sample_playlist.marshall();
	return 0;
}
