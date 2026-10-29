cmake_minimum_required(VERSION 3.20)
project(stm32_baremetal C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Chip selection: chips/<series>/<chip>/ -------------------------------
set(CHIP stm32f103x6 CACHE STRING "Target chip (folder name under chips/<series>/)")

file(GLOB CHIP_MATCHES LIST_DIRECTORIES true ${CMAKE_SOURCE_DIR}/chips/*/${CHIP})
list(LENGTH CHIP_MATCHES CHIP_MATCH_COUNT)
if(NOT CHIP_MATCH_COUNT EQUAL 1)
    message(FATAL_ERROR "CHIP '${CHIP}': expected exactly one folder chips/<series>/${CHIP}, found ${CHIP_MATCH_COUNT}")
endif()

set(CHIP_DIR ${CHIP_MATCHES})
get_filename_component(SERIES_DIR ${CHIP_DIR} DIRECTORY)

include(${SERIES_DIR}/seri.cmake)    # series: GPIO_BACKEND, CPU_FLAGS
include(${CHIP_DIR}/board.cmake)     # chip:   RAM_/FLASH_ ORIGIN and LENGTH

foreach(var GPIO_BACKEND CPU_FLAGS RAM_ORIGIN RAM_LENGTH FLASH_ORIGIN FLASH_LENGTH)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "${var} is not set by ${SERIES_DIR}/seri.cmake or ${CHIP_DIR}/board.cmake")
    endif()
endforeach()

# fill the @RAM_ORIGIN@ ... placeholders of the shared script for this chip
configure_file(${CMAKE_SOURCE_DIR}/chips/linker.ld ${CMAKE_BINARY_DIR}/linker.ld @ONLY)
set(LINKER_SCRIPT ${CMAKE_BINARY_DIR}/linker.ld)

# ---- Target -----------------------------------------------------------------
add_executable(firmware
    ${CHIP_DIR}/startup.c
    drivers/gpio/gpio_${GPIO_BACKEND}.c
    src/main.c
)
set_target_properties(firmware PROPERTIES
    SUFFIX ".elf"
    LINK_DEPENDS ${LINKER_SCRIPT}
)

target_include_directories(firmware PRIVATE
    ${SERIES_DIR}          # stm32f1.h / stm32f4.h
    drivers/gpio
)

target_compile_options(firmware PRIVATE
    ${CPU_FLAGS}
    -Wall -Wextra
    -O0 -gdwarf-4
    -ffunction-sections -fdata-sections
)

target_link_options(firmware PRIVATE
    ${CPU_FLAGS}
    -T${LINKER_SCRIPT}
    -nostartfiles
    --specs=nano.specs
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_BINARY_DIR}/firmware.map
    -Wl,--print-memory-usage
)

add_custom_command(TARGET firmware POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex $<TARGET_FILE:firmware> ${CMAKE_BINARY_DIR}/firmware.hex
    COMMENT "Generating firmware.hex"
)