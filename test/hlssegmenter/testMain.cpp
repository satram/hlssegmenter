/*
 * testMain.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#include "segmenterCommon.h"

#define INP_BUF_SIZE (100 * TS_PKT_SIZE_BYTES)


int main(int argc, char *argv[])
{

	/*
	 * Set the input config parameters
	 */
	ConfigParams config;
	config.playlist_type = event;
	config.segment_duration_ms = 10000;
	config.web_server_url = "http://192.168.1.10:8081/hlschunks/";
	config.output_folder = "/tmp/hlschunks/";

	variant_stream_info var1;
	var1.id = "quality1";
	var1.bandwidth = 52000;
	var1.generate_iframe_url = true;
	var1.vid.codec = h264video;
	var1.vid.profile = "baseline";
	var1.vid.level = 3.1;
	var1.vid.resolution = "1920x1080";
	var1.aud.codec = mpeg4audio_latm;
	var1.aud.subtype = "aac-lc";

	config.add_variant(var1);

	/*
	 * object for hls segmenter is created here
	 * this class can do segmentation based on config params
	 * and generate playlist as well
	 */
	Segmenter hls_segmenter(config);


    std::ifstream infile;
    infile.open(argv[1], std::ios::in | std::ios::binary);
    char *inp_buffer = new char[INP_BUF_SIZE];
    if(infile.is_open())
    {
        while(!infile.eof())
        {
        	infile.read(inp_buffer, INP_BUF_SIZE);
        	/*
        	 * send the input ts packets
        	 * both segmentation and playlist generation
        	 * happens inside this class
        	 */
        	hls_segmenter.parse_ts_packets(inp_buffer, INP_BUF_SIZE);
        }
        infile.close();
    }
    delete inp_buffer;

	return 0;
}
