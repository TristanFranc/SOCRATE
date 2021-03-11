################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/syscalls.c 

CPP_SRCS += \
../src/Timer_PWM.cpp \
../src/hardwareConfig.cpp \
../src/main.cpp 

C_DEPS += \
./src/syscalls.d 

OBJS += \
./src/Timer_PWM.o \
./src/hardwareConfig.o \
./src/main.o \
./src/syscalls.o 

CPP_DEPS += \
./src/Timer_PWM.d \
./src/hardwareConfig.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/Timer_PWM.o: ../src/Timer_PWM.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/CMSIS/core" -O0 -ffunction-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"src/Timer_PWM.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/hardwareConfig.o: ../src/hardwareConfig.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/CMSIS/core" -O0 -ffunction-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"src/hardwareConfig.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/main.o: ../src/main.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/CMSIS/core" -O0 -ffunction-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/syscalls.o: ../src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/TEMPLTE_VIDE_DRIVERS_SOCRATE/CMSIS/core" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

