################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ConfigParams.cpp \
../HlsPlaylistGenerator.cpp \
../IFramePlaylist.cpp \
../MasterPlaylist.cpp \
../MediaPlaylist.cpp \
../Segmenter.cpp 

OBJS += \
./ConfigParams.o \
./HlsPlaylistGenerator.o \
./IFramePlaylist.o \
./MasterPlaylist.o \
./MediaPlaylist.o \
./Segmenter.o 

CPP_DEPS += \
./ConfigParams.d \
./HlsPlaylistGenerator.d \
./IFramePlaylist.d \
./MasterPlaylist.d \
./MediaPlaylist.d \
./Segmenter.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


