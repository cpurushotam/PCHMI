################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BIOWrapper.cpp \
../src/BIO_Wrapper_Server.cpp 

CPP_DEPS += \
./src/BIOWrapper.d \
./src/BIO_Wrapper_Server.d 

OBJS += \
./src/BIOWrapper.o \
./src/BIO_Wrapper_Server.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/BIOWrapper.d ./src/BIOWrapper.o ./src/BIO_Wrapper_Server.d ./src/BIO_Wrapper_Server.o

.PHONY: clean-src

