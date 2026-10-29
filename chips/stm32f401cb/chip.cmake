# chips/stm32f401cb/chip.cmake
set(GPIO_BACKEND stm32f4)
set(CPU_FLAGS -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard)