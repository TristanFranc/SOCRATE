################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/syscalls.c \
../src/system_stm32f4xx.c 

CPP_SRCS += \
../src/AcquisitionEMG.cpp \
../src/CanalEMG.cpp \
../src/STM32F446Usart.cpp \
../src/Timer_PWM.cpp \
../src/VecteurEMG.cpp \
../src/controlL297.cpp \
../src/hardwareConfig.cpp \
../src/main.cpp 

C_DEPS += \
./src/syscalls.d \
./src/system_stm32f4xx.d 

OBJS += \
./src/AcquisitionEMG.o \
./src/CanalEMG.o \
./src/STM32F446Usart.o \
./src/Timer_PWM.o \
./src/VecteurEMG.o \
./src/controlL297.o \
./src/hardwareConfig.o \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f4xx.o 

CPP_DEPS += \
./src/AcquisitionEMG.d \
./src/CanalEMG.d \
./src/STM32F446Usart.d \
./src/Timer_PWM.d \
./src/VecteurEMG.d \
./src/controlL297.d \
./src/hardwareConfig.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/AcquisitionEMG.o: ../src/AcquisitionEMG.cpp src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/core" -O0 -ffunction-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"src/AcquisitionEMG.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/CanalEMG.o: ../src/CanalEMG.cpp src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/core" -O0 -ffunction-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"src/CanalEMG.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/STM32F446Usart.o: ../src/STM32F446Usart.cpp src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/core" -O0 -ffunction-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"src/STM32F446Usart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/Timer_PWM.o: ../src/Timer_PWM.cpp src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/core" -O0 -ffunction-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"src/Timer_PWM.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/VecteurEMG.o: ../src/VecteurEMG.cpp src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/core" -O0 -ffunction-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"src/VecteurEMG.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/controlL297.o: ../src/controlL297.cpp src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/core" -O0 -ffunction-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"src/controlL297.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/hardwareConfig.o: ../src/hardwareConfig.cpp src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/core" -O0 -ffunction-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"src/hardwareConfig.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/main.o: ../src/main.cpp src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/core" -O0 -ffunction-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/syscalls.o: ../src/syscalls.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/core" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/system_stm32f4xx.o: ../src/system_stm32f4xx.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -c -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/StdPeriph_Driver/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/inc" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/device" -I"C:/Users/201723940/STM32CubeIDE/workspace_1.5.1/SOCRATE/CMSIS/core" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"src/system_stm32f4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

