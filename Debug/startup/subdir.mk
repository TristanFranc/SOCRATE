################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

S_DEPS += \
./startup/startup_stm32.d 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/startup_stm32.o: ../startup/startup_stm32.s startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/core" -x assembler-with-cpp -MMD -MP -MF"startup/startup_stm32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

