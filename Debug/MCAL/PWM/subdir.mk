################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/PWM/PWM_config.c \
../MCAL/PWM/PWM_program.c 

OBJS += \
./MCAL/PWM/PWM_config.o \
./MCAL/PWM/PWM_program.o 

C_DEPS += \
./MCAL/PWM/PWM_config.d \
./MCAL/PWM/PWM_program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/PWM/%.o: ../MCAL/PWM/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

