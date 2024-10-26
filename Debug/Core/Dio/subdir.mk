################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Dio/dio.c 

OBJS += \
./Core/Dio/dio.o 

C_DEPS += \
./Core/Dio/dio.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Dio/%.o Core/Dio/%.su Core/Dio/%.cyclo: ../Core/Dio/%.c Core/Dio/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../Core/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc -I../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../Drivers/CMSIS/Include -I../Core/Dio -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Dio

clean-Core-2f-Dio:
	-$(RM) ./Core/Dio/dio.cyclo ./Core/Dio/dio.d ./Core/Dio/dio.o ./Core/Dio/dio.su

.PHONY: clean-Core-2f-Dio

