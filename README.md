hlssegmenter
============

hls segmenter tool supports master, child and i-frame playlist

----


TODO hlssegmenter
-----------------

mediaplaylist - support for live playlist

iframe playlist - support for live playlist

segmenter - handle eos, update playlist accordingly

Segmenter- make segmenter aware of multiple quality variants streams flowing through it. currently it is tied to one bitstream.

mediaplaylist - remove_node, update_section, add footer

iframe playlist - remove node, update section, footer

master playlist - remove section, remove node and update section

master playlist - config reading - support for multiple codecs, profiles, levels


TODO tsparser-cpp
-----------------

Bitstream.cpp - optimization - extend stream buf class to support move constructor - needed incase of memory buffer input

PES packet - optimization - copying of 100 bytes to PES data byte - improve this design 


TODO testing
------------

file input, 1 quality, publish media/iframe playlist as EVENT, convert it to VOD at end

file input, 1 quality, publish media/iframe playlist as LIVE

partial memory buffer input, 1 quality, publish media/iframe playlist as EVENT, convert it to VOD at end

partial memory buffer input, 1 quality, publish media/iframe playlist as LIVE


COMPLETED TASKS
---------------

Playlist type:Event is supported 

media playlist entries are updated OTF from ts packets

iframe playlist entries are updated OTF from ts packets

Doc - update uml diagram of hlssegmenter

playlist generation - write to a file and check it is growing

file writing - maintains context for all variants, context --> filename, path, byteoffset


----