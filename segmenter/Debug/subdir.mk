################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ConfigParams.cpp \
../IFramePlaylist.cpp \
../MasterPlaylist.cpp \
../testMain.cpp 

OBJS += \
./ConfigParams.o \
./IFramePlaylist.o \
./MasterPlaylist.o \
./testMain.o 

CPP_DEPS += \
./ConfigParams.d \
./IFramePlaylist.d \
./MasterPlaylist.d \
./testMain.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


