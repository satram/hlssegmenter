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
	prev_timestamp = 0;

    curr_chunk = new ChunkIndex();
    curr_chunk->set_interval(config.segment_duration_ms);
    chunk_index.push_back(curr_chunk);

}

Segmenter::~Segmenter()
{
	for(auto it = iframe_index.begin(), ite = iframe_index.end(); it != ite; it++)
		delete (*it);

	for(auto it = chunk_index.begin(), ite = chunk_index.end(); it != ite; it++)
		delete (*it);

	if(hls_playlist)
		delete hls_playlist;
}

void Segmenter::update_chunk(IFrameIndex *last_iframe)
{
	bool make_new_chunk = curr_chunk->update_chunk(last_iframe);
	if(make_new_chunk){
		curr_chunk = new ChunkIndex(last_iframe);
		chunk_index.push_back(curr_chunk);
	}
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

        	for(int i = 0; i < (*it)->detected_slice_type_count;i++)
            {
                if((*it)->slice_type[i].first == idr)
                {
                	if(iframe_index.size() > 0 && iframe_index.back() != 0)
                	{
                    	int duration_ms = ((*it)->pts - prev_timestamp)/TS_TIMESCALE_MILLISEC;
						IFrameIndex * last_iframe = iframe_index.back();
						last_iframe->finalize(accum_pktcount, duration_ms , accum_byteoffset);
						update_chunk(last_iframe);
                	}
                	//add new IDR entry
                    iframe_index.push_back(new IFrameIndex(accum_pktcount, accum_byteoffset));
                    prev_timestamp = (*it)->pts;
                }
                else if ((*it)->slice_type[i].first == non_idr)
                {
                	if(iframe_index.size() > 0)
                	{
                    	IFrameIndex * last_iframe = iframe_index.back();
                    	last_iframe->update(accum_pktcount, accum_byteoffset);
                	}
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
		if(curr->update_iframe_playlist.first && !curr->update_iframe_playlist.second)
		{
			hls_playlist->update_iframe(curr);
			curr->update_iframe_playlist.second = true;
			hls_playlist->publish_playlist();
		}
	}

	for(unsigned int i = 0; i < chunk_index.size(); i++)
	{
		ChunkIndex * curr = chunk_index[i];
		if(curr->update_media_playlist.first && !curr->update_media_playlist.second)
		{
			hls_playlist->update_media(curr);
			curr->update_media_playlist.second = true;
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
    hls_playlist->publish_media(inp_buffer, bufsize);

    ts_packet_count += input_ts_stream.get_num_packets();
    byte_offset += bufsize;

    std::cout << "ts_packet_count " << ts_packet_count << std::endl;

    input_ts_stream.close();
}

void Segmenter::finalize_playlist()
{
	hls_playlist->finalize_playlist();
	hls_playlist->publish_playlist();
}
