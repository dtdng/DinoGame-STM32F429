################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TM_RNG/Src/FLASH_SECTOR_F4.c \
../TM_RNG/Src/tm_stm32f4_rng.c 

C_DEPS += \
./TM_RNG/Src/FLASH_SECTOR_F4.d \
./TM_RNG/Src/tm_stm32f4_rng.d 

OBJS += \
./TM_RNG/Src/FLASH_SECTOR_F4.o \
./TM_RNG/Src/tm_stm32f4_rng.o 


# Each subdirectory must supply rules for building sources it contributes
TM_RNG/Src/%.o TM_RNG/Src/%.su TM_RNG/Src/%.cyclo: ../TM_RNG/Src/%.c TM_RNG/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUSE_BPP=16 -DDEBUG -DSTM32F429xx -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/target/generated -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -I"D:/20222/EmbeddedCat/STM32CubeIDE/TM_RNG/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TM_RNG-2f-Src

clean-TM_RNG-2f-Src:
	-$(RM) ./TM_RNG/Src/FLASH_SECTOR_F4.cyclo ./TM_RNG/Src/FLASH_SECTOR_F4.d ./TM_RNG/Src/FLASH_SECTOR_F4.o ./TM_RNG/Src/FLASH_SECTOR_F4.su ./TM_RNG/Src/tm_stm32f4_rng.cyclo ./TM_RNG/Src/tm_stm32f4_rng.d ./TM_RNG/Src/tm_stm32f4_rng.o ./TM_RNG/Src/tm_stm32f4_rng.su

.PHONY: clean-TM_RNG-2f-Src

