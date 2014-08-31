cmake_minimum_required(VERSION 2.8)

set(CMAKE_SYSTEM_NAME Linux)

if (DEFINED ENV{CC})
	message($ENV{CC})
endif()

if (DEFINED ENV{CXX})
	message($ENV{CXX})
endif()

if (DEFINED ENV{CROSS_COMPILE})
	add_definitions(-DCROSS_COMPILE)
	include_directories("$ENV{LOCAL_STAGING}/usr/include")

	link_directories("$ENV{LOCAL_STAGING}/lib")
	link_directories("$ENV{LOCAL_STAGING}/usr/lib")
	link_directories("$ENV{OCAPROOT}/bin/$ENV{OCAPTC}/bin/")
	link_directories("$ENV{OCAPROOT}/bin/$ENV{OCAPTC}/bin/usr/lib")
	link_directories("$ENV{OCAPROOT}/bin/$ENV{OCAPTC}/bin/rstreamer/lib")
	link_directories("$ENV{OCAPROOT}/bin/$ENV{OCAPTC}/bin/rstreamer/usr/lib")
	
	link_directories("/opt/ramdisk/dsg_dir/lib/dsg_rpc_cm2h")
	link_directories("/opt/ramdisk/dsg_dir/lib/dsg_rpc_h2cm")
	link_directories("/opt/ramdisk/dsg_dir/lib/htx_dsg_lib")

else()
	link_directories(/usr/local/lib)
endif()

set(CMAKE_CXX_FLAGS "-O0 -g3 -Wall -fPIC -std=c++0x -D_GLIBCXX_USE_NANOSLEEP")

add_subdirectory(mediatools)
add_subdirectory(segmenter)
add_subdirectory(transcode)

add_subdirectory(test/TranscoderTest)
add_subdirectory(test/hlssegmenter)
add_subdirectory(test/m3u8writer)
add_subdirectory(test/tsparser)

