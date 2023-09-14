################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/ICU_HW/ICU_Config.c \
../MCAL/ICU_HW/ICU_program.c 

OBJS += \
./MCAL/ICU_HW/ICU_Config.o \
./MCAL/ICU_HW/ICU_program.o 

C_DEPS += \
./MCAL/ICU_HW/ICU_Config.d \
./MCAL/ICU_HW/ICU_program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/ICU_HW/%.o: ../MCAL/ICU_HW/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


