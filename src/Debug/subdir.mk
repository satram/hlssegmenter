################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AudioStream.cpp \
../Bitstream.cpp \
../ParseAdaptationField.cpp \
../ParsePESPacket.cpp \
../ParseTsHeader.cpp \
../ParseTsStream.cpp \
../PatParse.cpp \
../PmtParse.cpp \
../Profiler.cpp \
../SectionHeader.cpp \
../TsPacket.cpp \
../VideoStream.cpp 

OBJS += \
./AudioStream.o \
./Bitstream.o \
./ParseAdaptationField.o \
./ParsePESPacket.o \
./ParseTsHeader.o \
./ParseTsStream.o \
./PatParse.o \
./PmtParse.o \
./Profiler.o \
./SectionHeader.o \
./TsPacket.o \
./VideoStream.o 

CPP_DEPS += \
./AudioStream.d \
./Bitstream.d \
./ParseAdaptationField.d \
./ParsePESPacket.d \
./ParseTsHeader.d \
./ParseTsStream.d \
./PatParse.d \
./PmtParse.d \
./Profiler.d \
./SectionHeader.d \
./TsPacket.d \
./VideoStream.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../include -I../../include/m3u8 -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


