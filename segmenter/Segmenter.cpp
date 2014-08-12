/*
 * Segmenter.cpp
 *
 *  Created on: Aug 7, 2014
 *      Author: satram
 */

#include "Segmenter.h"

Segmenter::Segmenter(ConfigParams &config)
{
	hls_playlist = new HlsPlaylistGenerator(config);
	hls_playlist->generate_header(config);
	hls_playlist->publish_playlist();
	ts_packet_count = 0;
	byte_offset = 0;
	segment_duration = config.segment_duration_ms;
}

Segmenter::~Segmenter()
{
	for(auto it = iframe_index.begin(), ite = iframe_index.end(); it != ite; it++)
		delete (*it);

	if(hls_playlist)
		delete hls_playlist;
}

void Segmenter::create_index_table()
{
    std::list<VideoPktInfo*> pkt_list = input_ts_stream.get_pkt_info();
    for(auto it = pkt_list.begin(), ite = pkt_list.end();it != ite;it++)
    {
        if((*it)->PUSI_flag)
        {
        	int accum_pktcount = ts_packet_count + (*it)->pkt_count;
        	long long accum_byteoffset = (*it)->byte_offset + byte_offset;
        	long long timestamp = (*it)->dts;
            for(int i = 0; i < (*it)->detected_slice_type_count;i++)
            {
                if((*it)->slice_type[i].first == idr)
                {
                	IFrameIndex * last_iframe = 0;

                	if(iframe_index.size() > 0)
                	{
                    	last_iframe = iframe_index.back();

                    	//finalize iframe entry
                    	if(last_iframe != 0)
                    	{
                    		last_iframe->finalize(accum_pktcount, timestamp , accum_byteoffset);
                        	//check and finalize chunk entry
                        	if(last_iframe->duration_from_chunk_start > segment_duration)
                        	{
                        		for(int i = iframe_index.size() - 1; i > 0; i--)
                        		{
                        			if(iframe_index[i] == last_iframe && (i > 0))
                        			{
                                		IFrameIndex *penultimate_iframe = iframe_index[i-1];
                                		//finalize chunk on penultimate iframe
                                		if(penultimate_iframe != 0)
                                		{
                                			penultimate_iframe->finalize_chunk();
            								//start the chunk on last iframe
            								last_iframe->start_chunk();
                                		}
                        			}
                        		}
                        	}
                    	}
                	}

                	//add new IDR entry
                    iframe_index.push_back(new IFrameIndex(accum_pktcount, timestamp , accum_byteoffset));

                    //start the chunk on the very first iframe index
                    if(last_iframe == 0)
                    {
                    	last_iframe = iframe_index.back();
                    	last_iframe->start_chunk();
                    }
                }
                else if ((*it)->slice_type[i].first == non_idr)
                {
                	IFrameIndex * last_iframe = iframe_index.back();
                	last_iframe->update(accum_pktcount, timestamp , accum_byteoffset);
                }
            }
        }
    }
}

void Segmenter::update_playlists()
{
	for(unsigned int i = 0; i < iframe_index.size(); i++)
	{
		IFrameIndex * curr = iframe_index[i];
		if(curr->flags.update_media_playlist.first && !curr->flags.update_media_playlist.second)
		{
			hls_playlist->update_media(curr);
			curr->flags.update_media_playlist.second = true;
			hls_playlist->publish_playlist();
		}
		if(curr->flags.update_iframe_playlist.first && !curr->flags.update_iframe_playlist.second)
		{
			hls_playlist->update_iframe(curr);
			curr->flags.update_iframe_playlist.second = true;
			hls_playlist->publish_playlist();
		}
	}
}



void Segmenter::parse_ts_packets(const char *inp_buffer, int bufsize)
{
    input_ts_stream.open(inp_buffer, bufsize);
    input_ts_stream.parse_bytestream();

    create_index_table();
    update_playlists();

    ts_packet_count += input_ts_stream.get_num_packets();
    byte_offset += bufsize;

    std::cout << "ts_packet_count " << ts_packet_count << std::endl;

    input_ts_stream.close();
}


