################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ChunkIndex.cpp \
../ConfigParams.cpp \
../HlsPlaylistGenerator.cpp \
../IFrameIndex.cpp \
../IFramePlaylist.cpp \
../IndexBase.cpp \
../MasterPlaylist.cpp \
../MediaPlaylist.cpp \
../PlaylistInterface.cpp \
../Segmenter.cpp \
../VariantPlaylist.cpp 

OBJS += \
./ChunkIndex.o \
./ConfigParams.o \
./HlsPlaylistGenerator.o \
./IFrameIndex.o \
./IFramePlaylist.o \
./IndexBase.o \
./MasterPlaylist.o \
./MediaPlaylist.o \
./PlaylistInterface.o \
./Segmenter.o \
./VariantPlaylist.o 

CPP_DEPS += \
./ChunkIndex.d \
./ConfigParams.d \
./HlsPlaylistGenerator.d \
./IFrameIndex.d \
./IFramePlaylist.d \
./IndexBase.d \
./MasterPlaylist.d \
./MediaPlaylist.d \
./PlaylistInterface.d \
./Segmenter.d \
./VariantPlaylist.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


