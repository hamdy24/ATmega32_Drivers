################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/SWITCH_LINKING/Switch_config.c \
../HAL/SWITCH_LINKING/Switch_prog.c 

OBJS += \
./HAL/SWITCH_LINKING/Switch_config.o \
./HAL/SWITCH_LINKING/Switch_prog.o 

C_DEPS += \
./HAL/SWITCH_LINKING/Switch_config.d \
./HAL/SWITCH_LINKING/Switch_prog.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/SWITCH_LINKING/%.o: ../HAL/SWITCH_LINKING/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


