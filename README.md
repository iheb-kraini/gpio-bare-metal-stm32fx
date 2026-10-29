# STM32F103 Bare-Metal Firmware (no HAL, no IDE)

A from-scratch bare-metal project for the **STM32F103C6** (Cortex-M3): hand-written linker script, startup code and vector table, a CMake cross-compilation build, and a register-level GPIO driver with a chip-independent public API.

No HAL, no CubeMX-generated code, and no IDE project files. Everything between power-on and `main()` is written and explained in this repo.

> **Status:** builds cleanly, links to the expected memory layout, and blinks an LED in **Proteus simulation**. It has not been run on physical hardware yet.

## Why this project

To understand what happens before `main()` runs and to build an embedded project from first principles. Vendor tooling normally hides that, so this repo does without it.

## What's implemented

- **Linker script** (`stm32f103x6.ld`): FLASH/RAM memory map for the 32 KB / 10 KB part, `.isr_vector` pinned to the start of flash (`KEEP`), `.data` stored in flash but linked to run in RAM (`>RAM AT> FLASH`), `.bss`, and a heap/stack reservation check.
- **Startup code** (`startup.c`): 59-entry Cortex-M3 vector table for the F103x6 interrupt set, placed in its own section. Every handler is a weak alias of `Default_Handler`, so defining a function with the right name overrides it with no table edits. `Reset_Handler` copies `.data` from flash to RAM, zeroes `.bss`, and calls `main()`.
- **Chip header** (`stm32f103x6.h`): peripheral base addresses, register structs (`RCC_TypeDef`, `GPIO_TypeDef`) and bit masks written from RM0008. The struct field order matches the register offsets.
- **GPIO driver**: a public header that describes intent (mode, pull, speed) and an F1 implementation that translates it to the F1's `CRL`/`CRH` CNF/MODE nibbles and the `ODR`-bit pull-up/pull-down scheme.
- **Build system**: CMake + Ninja with an `arm-none-eabi` toolchain file, `-ffunction-sections`/`--gc-sections`, a linker map, memory-usage output, and automatic `.hex` generation after each build.

## Project structure

```
.
├── CMakeLists.txt
├── cmake/
│   └── arm-none-eabi.cmake      # cross-compile toolchain file
├── chips/
│   └── stm32f103x6/
│       ├── startup.c            # vector table + Reset_Handler
│       ├── stm32f103x6.ld       # linker script
│       └── stm32f103x6.h        # registers, structs, bit masks
├── drivers/
│   └── gpio/
│       ├── gpio.h               # public, chip-independent API
│       └── gpio.c               # STM32F1 implementation
└── src/
    └── main.c                   # application (LED blink)
```

Chip-specific files (startup, linker script, register header) live under `chips/`. The driver's public header does not include the chip header, so application code never sees register names.

## How boot works

1. At reset the CPU loads the stack pointer from word 0 of the vector table (`_estack`, the end of RAM) and jumps to the address in word 1 (`Reset_Handler`, Thumb bit set).
2. `Reset_Handler` copies initialised globals from their flash load address (`_sidata`) to RAM (`_sdata`..`_edata`) and zeroes `.bss` (`_sbss`..`_ebss`).
3. It calls `main()`, and loops forever if `main` ever returns.

## GPIO driver API

```c
int gpio_enable(gpio_port_t port);                 // enable the port's clock
int gpio_config_pin(gpio_port_t port,
                    gpio_config_t config,
                    uint16_t pin_num);             // mode / pull / speed
int gpio_set(gpio_port_t port, uint16_t mask);     // drive pins high
int gpio_clear(gpio_port_t port, uint16_t mask);   // drive pins low
```

Example (`src/main.c`):

```c
gpio_enable(GPIO_PORT_A);
gpio_config_t led = { .mode  = GPIO_MODE_OUTPUT_PP,
                      .pull  = GPIO_PULL_NONE,
                      .speed = GPIO_SPEED_LOW };
gpio_config_pin(GPIO_PORT_A, led, 2);

while (1) {
  gpio_set(GPIO_PORT_A, GPIO_PIN(2));
  /* delay */
  gpio_clear(GPIO_PORT_A, GPIO_PIN(2));
  /* delay */
}
```

`gpio_config_t` separates **mode**, **pull** and **speed** instead of exposing the F1's CNF/MODE encoding. That keeps the public header free of F1-specific terms, so another register model (e.g. STM32F4's `MODER`/`PUPDR`) could be added as a second implementation file.

## Build

Requirements: `arm-none-eabi-gcc` (developed with GNU Tools for STM32 13.3), CMake 3.20+, Ninja.

```powershell
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake
cmake --build build
```

Outputs in `build/`: `firmware.elf`, `firmware.hex`, `firmware.map`. The link step prints Flash and RAM usage.

## Verifying the result

Check the memory layout and the vector table:

```powershell
arm-none-eabi-objdump -h build/firmware.elf
arm-none-eabi-objdump -s -j .isr_vector build/firmware.elf
```

Expected:

- `.isr_vector` at `0x08000000`, size `0xEC` (59 words)
- `.data` linked to RAM (`0x2000....`) with its load address in flash
- first vector word `0x20002800` (end of the 10 KB RAM), second word `Reset_Handler` with the Thumb bit set

## Simulation

Load `build/firmware.hex` (or the `.elf`) into a Proteus STM32F103C6 model with an LED on the configured pin. The `.elf` is built with `-gdwarf-4`, because Proteus's ELF loader rejected the DWARF 5 that GCC 13 emits by default.

## Known limitations and next steps

- Verified in simulation only, not yet on hardware.
- `gpio_set`/`gpio_clear` use read-modify-write on `ODR`, and should move to `BSRR` for atomic updates.
- No clock setup: the chip runs on its reset-default clock, and the blink delay is a busy loop. Next: PLL configuration and a SysTick-based delay.
- Only one chip is supported. The structure is meant to allow a second backend, but that's not written yet, so the API's portability is untested.
