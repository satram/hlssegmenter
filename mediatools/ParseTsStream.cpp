/*
 * ParseTsStream.cpp
 *
 *  Created on: Jul 2, 2014
 *      Author: satram
 */

#include "ParseTsStream.h"
#include "ElementaryStream.h"
#include "VideoStream.h"
#include "AudioStream.h"
#include "TsPacket.h"
#include "PatParse.h"
#include "PmtParse.h"


//class related
ParseTsStream::ParseTsStream()
{
	log4c_init();
	pat_packet = new PatParse();
    pmt_packet = new PmtParse();
    ts_packet_count = 1;
	mycat = log4c_category_get("tsparser.tsstream");

    input_memcopy = Profiler("input_memcpy");
    pes_pkt_copy = Profiler("pes_pktcopy");
    ts_pkt_profiler = Profiler("overall");
    video_pkt_profiler = Profiler("vidpkt_parsing");
    audio_pkt_profiler = Profiler("audpkt_parsing");

}


ParseTsStream::~ParseTsStream() {
//	ts_pkt_profiler.print_stats();
//	video_pkt_profiler.print_stats();
//	audio_pkt_profiler.print_stats();
//	input_memcopy.print_stats();
//	pes_pkt_copy.print_stats();
	delete pat_packet;
	delete pmt_packet;
	if ( log4c_fini()){
		  log4c_category_log(mycat, LOG4C_PRIORITY_ERROR,"log4c_fini() failed");
	  }
}


//input operations
void ParseTsStream::open(std::string & inpFile)
{
	ts_packet_count = 1;
    video_stream = new VideoStream();
    audio_stream = new AudioStream();
    bitstream.open(inpFile);
}

void ParseTsStream::open(std::streambuf *rdbuf)
{
	ts_packet_count = 1;
    video_stream = new VideoStream();
    audio_stream = new AudioStream();
    bitstream.open(rdbuf);
}

void ParseTsStream::open(const char *buf, int length)
{
	ts_packet_count = 1;
    video_stream = new VideoStream();
    audio_stream = new AudioStream();
	input_memcopy.start_timer();
    bitstream.open(buf, length);
    input_memcopy.record_elapsed_time();
}

void ParseTsStream::close()
{
	delete video_stream;
	delete audio_stream;
	bitstream.close();
	pid_list.clear();
}

//core parsing

void ParseTsStream::parse_bytestream()
{

    TsPacket *ts_packet;
    int pid;
    while(1){

    	ts_pkt_profiler.start_timer();

        //loop over each TS packet
        log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "---------------------------");
        log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "Parsing Packet #%d", ts_packet_count);
        try {
            //parse the packet TS header and adaptation field
            ts_packet = new TsPacket(ts_packet_count);
            ts_packet->input_bitstream(bitstream);
            update_pid_list(pid);
            //pid based switches
            pid = ts_packet->get_pid();
            if(pid == 0){
                pat_packet->input_bitstream(bitstream, pid);
                pmt_pid = pat_packet->get_pmt_pid();
                log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "pmt_pid %d (hex %x)", pmt_pid, pmt_pid);
                ts_packet->skip_to_end(bitstream);
            }else
                if(pmt_pid != 0 && (pid == pmt_pid)){
                    pmt_packet->input_bitstream(bitstream);
                    int streamtype;
                    video_pid = pmt_packet->get_video_pid(streamtype);
                    log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "video_pid %d (hex %x)", video_pid, video_pid);
                    video_stream->start_recording(streamtype, video_pid);
                    audio_pid = pmt_packet->get_audio_pid(streamtype);
                    log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "audio_pid %d (hex %x)", audio_pid, audio_pid);
                    audio_stream->start_recording(streamtype, audio_pid);
                    ts_packet->skip_to_end(bitstream);
                }else{
                    bool parse_data = false;
                    if(pid == video_pid || pid == audio_pid){
                        log4c_category_log(mycat, LOG4C_PRIORITY_TRACE, "parsing data bytes in this packet");
                        parse_data = true;
                    }
                    if(ts_packet->get_PUSI_flag())
                    	pes_pkt_copy.start_timer();
                    ts_packet->parse_data_byte(bitstream, parse_data);
                    if(ts_packet->get_PUSI_flag())
                    	pes_pkt_copy.record_elapsed_time();
                }


        }
        catch(std::exception & e){
            log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "%s", e.what());
            if(e.what() != nullptr)
            	std::cout << e.what() << std::endl;
            ts_packet->skip_to_end(bitstream);
        }
        //save the packets data in program stream, video or audio stream
        if(pid == 0 || pid == pmt_pid)
        {
            ts_pkt_list.push_back(ts_packet);
        }
        else
        {
            if(pid == video_pid)
            {
            	video_pkt_profiler.start_timer();
            	video_stream->insert_pkt(ts_packet);
                video_pkt_profiler.record_elapsed_time();
            }
            else if(pid == audio_pid)
            {
            	audio_pkt_profiler.start_timer();
            	audio_stream->insert_pkt(ts_packet);
                audio_pkt_profiler.record_elapsed_time();
            }
        }

        ts_pkt_profiler.record_elapsed_time();
        delete ts_packet;
        ts_packet_count++;
        if(bitstream.is_eof() || (bitstream.get_in_byte_offset() < 0))
            break;

    }
}

//statistics

void ParseTsStream::update_pid_list(int & pid)
{
    std::map<int,int>::iterator it = pid_list.find(pid);
    int count = 0;
    if(it != pid_list.end()){
        count = it->second;
        pid_list[pid] = (++count);
    }else
        pid_list.insert(std::pair<int,int>(pid, ++count));

}

void ParseTsStream::print_pid_list()
{
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "------------------------------");
	log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "PID -- COUNT");
	for(auto it = pid_list.begin(), ite = pid_list.end(); it != ite; it++)
	{
		log4c_category_log(mycat, LOG4C_PRIORITY_INFO, "%4d -- %8d", it->first, it->second);
	}
}

int ParseTsStream::get_num_packets()
{
	int num_pkts = 0;
	for(auto it = pid_list.begin(), ite = pid_list.end(); it != ite; it++)
	{
		num_pkts += it->second;
	}
	return num_pkts;
}

void ParseTsStream::print_stats()
{
	video_stream->print_stats();
	audio_stream->print_stats();
}

std::list<VideoPktInfo *> &ParseTsStream::get_pkt_info()
{
	return (video_stream->get_pkt_info());
}
