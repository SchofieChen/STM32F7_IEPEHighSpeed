################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/ComplexMathFunctions/arm_cmplx_conj_f32.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_conj_q15.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_conj_q31.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_f32.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_q15.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_q31.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_mag_f32.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_mag_q15.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_mag_q31.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_f32.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_q15.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_q31.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_f32.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_q15.c \
../Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_q31.c 

OBJS += \
./Core/Inc/ComplexMathFunctions/arm_cmplx_conj_f32.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_conj_q15.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_conj_q31.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_f32.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_q15.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_q31.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mag_f32.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mag_q15.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mag_q31.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_f32.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_q15.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_q31.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_f32.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_q15.o \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_q31.o 

C_DEPS += \
./Core/Inc/ComplexMathFunctions/arm_cmplx_conj_f32.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_conj_q15.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_conj_q31.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_f32.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_q15.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_q31.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mag_f32.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mag_q15.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mag_q31.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_f32.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_q15.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_q31.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_f32.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_q15.d \
./Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/ComplexMathFunctions/arm_cmplx_conj_f32.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_conj_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_conj_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_conj_q15.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_conj_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_conj_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_conj_q31.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_conj_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_conj_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_f32.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_q15.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_q31.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_dot_prod_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_mag_f32.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_mag_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_mag_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_mag_q15.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_mag_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_mag_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_mag_q31.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_mag_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_mag_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_f32.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_q15.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_q31.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_mag_squared_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_f32.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_q15.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_q15.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_q15.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_q31.o: ../Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F767xx -DARM_MATH_CM7 -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/ComplexMathFunctions/arm_cmplx_mult_real_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

