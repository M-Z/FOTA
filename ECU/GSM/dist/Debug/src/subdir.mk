################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/AFIO_program.c \
../src/Application.c \
../src/CAN.c \
../src/CANHANDLER_prog.c \
../src/DIO_prog.c \
../src/DMA_program.c \
../src/GSMHANDLER_prog.c \
../src/GSM_program.c \
../src/NVIC_prog.c \
../src/RCC_prog.c \
../src/RTC_prog.c \
../src/SCB_prog.c \
../src/SCH_prog.c \
../src/SYSTICK_prog.c \
../src/Timer_prog.c \
../src/USART_program.c \
../src/_write.c \
../src/main.c

OBJS += \
./src/AFIO_program.o \
./src/Application.o \
./src/CAN.o \
./src/CANHANDLER_prog.o \
./src/DIO_prog.o \
./src/DMA_program.o \
./src/GSMHANDLER_prog.o \
./src/GSM_program.o \
./src/NVIC_prog.o \
./src/RCC_prog.o \
./src/RTC_prog.o \
./src/SCB_prog.o \
./src/SCH_prog.o \
./src/SYSTICK_prog.o \
./src/Timer_prog.o \
./src/USART_program.o \
./src/_write.o \
./src/main.o

C_DEPS += \
./src/AFIO_program.d \
./src/Application.d \
./src/CAN.d \
./src/CANHANDLER_prog.d \
./src/DIO_prog.d \
./src/DMA_program.d \
./src/GSMHANDLER_prog.d \
./src/GSM_program.d \
./src/NVIC_prog.d \
./src/RCC_prog.d \
./src/RTC_prog.d \
./src/SCB_prog.d \
./src/SCH_prog.d \
./src/SYSTICK_prog.d \
./src/Timer_prog.d \
./src/USART_program.d \
./src/_write.d \
./src/main.d


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
