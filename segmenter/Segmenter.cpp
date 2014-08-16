/*
 * Segmenter.cpp
 *
 *  Created on: Aug 7, 2014
 *      Author: satram
 */

#include "Segmenter.h"
#include "HlsPlaylistGenerator.h"
#include "ChunkIndex.h"
#include "IFrameIndex.h"

Segmenter::Segmenter(ConfigParams &config)
{
	hls_playlist = new HlsPlaylistGenerator(config);
	hls_playlist->generate_header(config);
	hls_playlist->publish_playlist();
	ts_packet_count = 0;
	byte_offset = 0;

	segment_duration = config.segment_duration_ms;
	sliding_window_duration = config.sliding_window_duration_ms;
	playlist_type = config.playlist_type;

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

void Segmenter::update_chunk_index(IFrameIndex *last_iframe)
{
	bool make_new_chunk = curr_chunk->update_chunk(last_iframe);
	if(make_new_chunk){
		curr_chunk = new ChunkIndex(last_iframe);
		chunk_index.push_back(curr_chunk);
	}
}

void Segmenter::update_iframe_index()
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
						IFrameIndex * last_iframe = dynamic_cast<IFrameIndex *> (iframe_index.back());
						last_iframe->finalize(accum_pktcount, duration_ms , accum_byteoffset);
						update_chunk_index(last_iframe);
                	}
                	//add new IDR entry
                    iframe_index.push_back(new IFrameIndex(accum_pktcount, accum_byteoffset));
                    prev_timestamp = (*it)->pts;
                }
                else if ((*it)->slice_type[i].first == non_idr)
                {
                	if(iframe_index.size() > 0)
                	{
                    	IFrameIndex * last_iframe = dynamic_cast<IFrameIndex *> (iframe_index.back());
                    	last_iframe->update(accum_pktcount, accum_byteoffset);
                	}
                }
            }
        }
    }
}

void Segmenter::check_index_add(std::list<IndexBase *> &index)
{
    for(auto it = index.begin(), ite = index.end(); it != ite; it++)
    {
        if((*it)->add_to_playlist.first && !(*it)->add_to_playlist.second)
        {
            hls_playlist->update(*it, true);
            (*it)->add_to_playlist.second = true;
			update_playlist = true;
        }
    }
}

void Segmenter::check_index_remove(std::list<IndexBase *> &index)
{
	unsigned int current_sliding_window_duration = 0;
	bool remove_entry = false;
	for(auto it = index.rbegin(), ite = index.rend(); it != ite; it++)
	{
		if(remove_entry)
		{
			(*it)->purge = true;
			continue;
		}
		current_sliding_window_duration += (*it)->duration;
		if(current_sliding_window_duration > sliding_window_duration)
			remove_entry = true;
	}
	for(auto it = index.begin(), ite = index.end(); it != ite; it++)
	{
		if((*it)->purge)
		{
			it = index.erase(it);
			hls_playlist->update(*it, false);
			update_playlist = true;
		}
	}
}

void Segmenter::update_playlists()
{
	update_playlist = false;
    check_index_add(iframe_index);
    check_index_add(chunk_index);
    if(playlist_type == LIVE)
    {
		check_index_remove(iframe_index);
		check_index_remove(chunk_index);
    }
    if(update_playlist)
    	hls_playlist->publish_playlist();
}



void Segmenter::parse_ts_packets(const char *inp_buffer, int bufsize)
{
    input_ts_stream.open(inp_buffer, bufsize);
    input_ts_stream.parse_bytestream();

    update_iframe_index();
    update_playlists();
    hls_playlist->publish_media(inp_buffer, bufsize);

    ts_packet_count += input_ts_stream.get_num_packets();
    byte_offset += bufsize;

    std::cout << "ts_packet_count " << ts_packet_count << std::endl;

    input_ts_stream.close();
}

void Segmenter::finalize_playlist()
{
	if(playlist_type != LIVE)
		hls_playlist->finalize_playlist();
	hls_playlist->publish_playlist();
}
