#include <stdint.h>
#include <string.h>

/* Symbols from link.ld: these are addresses, not variables */
extern uint32_t _estack;
extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss;

int main(void);

/* Defined by you in this file */
void Reset_Handler(void);
void Default_Handler(void);

/* ---- Core exceptions (weak, default to Default_Handler) ---- */
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

/* ---- Peripheral interrupts (STM32F401 set) ---- */
void WWDG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream0_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream1_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream2_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream3_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream4_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream5_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream6_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void ADC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_FS_WKUP_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream7_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void SDIO_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream0_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream1_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream2_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream3_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream4_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream7_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void USART6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void FPU_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));

/* ---- Vector table for STM32F401 ---- */
__attribute__((section(".isr_vector"), used)) const uintptr_t vector_table[] = {
    (uintptr_t)&_estack,           /* 0  initial SP         */
    (uintptr_t)Reset_Handler,      /* 1  Reset              */
    (uintptr_t)NMI_Handler,        /* 2  NMI                */
    (uintptr_t)HardFault_Handler,  /* 3  HardFault          */
    (uintptr_t)MemManage_Handler,  /* 4  MemManage          */
    (uintptr_t)BusFault_Handler,   /* 5  BusFault           */
    (uintptr_t)UsageFault_Handler, /* 6  UsageFault         */
    0,
    0,
    0,
    0,                           /* 7-10 reserved        */
    (uintptr_t)SVC_Handler,      /* 11 SVCall            */
    (uintptr_t)DebugMon_Handler, /* 12 DebugMon          */
    0,                           /* 13 reserved          */
    (uintptr_t)PendSV_Handler,   /* 14 PendSV            */
    (uintptr_t)SysTick_Handler,  /* 15 SysTick           */

    /* peripheral interrupts: slot = 16 + position */
    (uintptr_t)WWDG_IRQHandler,               /* pos 0  */
    (uintptr_t)PVD_IRQHandler,                /* pos 1  */
    (uintptr_t)TAMP_STAMP_IRQHandler,         /* pos 2  */
    (uintptr_t)RTC_WKUP_IRQHandler,           /* pos 3  */
    (uintptr_t)FLASH_IRQHandler,              /* pos 4  */
    (uintptr_t)RCC_IRQHandler,                /* pos 5  */
    (uintptr_t)EXTI0_IRQHandler,              /* pos 6  */
    (uintptr_t)EXTI1_IRQHandler,              /* pos 7  */
    (uintptr_t)EXTI2_IRQHandler,              /* pos 8  */
    (uintptr_t)EXTI3_IRQHandler,              /* pos 9  */
    (uintptr_t)EXTI4_IRQHandler,              /* pos 10 */
    (uintptr_t)DMA1_Stream0_IRQHandler,       /* pos 11 */
    (uintptr_t)DMA1_Stream1_IRQHandler,       /* pos 12 */
    (uintptr_t)DMA1_Stream2_IRQHandler,       /* pos 13 */
    (uintptr_t)DMA1_Stream3_IRQHandler,       /* pos 14 */
    (uintptr_t)DMA1_Stream4_IRQHandler,       /* pos 15 */
    (uintptr_t)DMA1_Stream5_IRQHandler,       /* pos 16 */
    (uintptr_t)DMA1_Stream6_IRQHandler,       /* pos 17 */
    (uintptr_t)ADC_IRQHandler,                /* pos 18 */
    0,                                        /* pos 19 reserved */
    0,                                        /* pos 20 reserved */
    0,                                        /* pos 21 reserved */
    0,                                        /* pos 22 reserved */
    (uintptr_t)EXTI9_5_IRQHandler,            /* pos 23 */
    (uintptr_t)TIM1_BRK_TIM9_IRQHandler,      /* pos 24 */
    (uintptr_t)TIM1_UP_TIM10_IRQHandler,      /* pos 25 */
    (uintptr_t)TIM1_TRG_COM_TIM11_IRQHandler, /* pos 26 */
    (uintptr_t)TIM1_CC_IRQHandler,            /* pos 27 */
    (uintptr_t)TIM2_IRQHandler,               /* pos 28 */
    (uintptr_t)TIM3_IRQHandler,               /* pos 29 */
    (uintptr_t)TIM4_IRQHandler,               /* pos 30 */
    (uintptr_t)I2C1_EV_IRQHandler,            /* pos 31 */
    (uintptr_t)I2C1_ER_IRQHandler,            /* pos 32 */
    (uintptr_t)I2C2_EV_IRQHandler,            /* pos 33 */
    (uintptr_t)I2C2_ER_IRQHandler,            /* pos 34 */
    (uintptr_t)SPI1_IRQHandler,               /* pos 35 */
    (uintptr_t)SPI2_IRQHandler,               /* pos 36 */
    (uintptr_t)USART1_IRQHandler,             /* pos 37 */
    (uintptr_t)USART2_IRQHandler,             /* pos 38 */
    0,                                        /* pos 39 reserved */
    (uintptr_t)EXTI15_10_IRQHandler,          /* pos 40 */
    (uintptr_t)RTC_Alarm_IRQHandler,          /* pos 41 */
    (uintptr_t)OTG_FS_WKUP_IRQHandler,        /* pos 42 */
    0,                                        /* pos 43 reserved */
    0,                                        /* pos 44 reserved */
    0,                                        /* pos 45 reserved */
    0,                                        /* pos 46 reserved */
    (uintptr_t)DMA1_Stream7_IRQHandler,       /* pos 47 */
    (uintptr_t)SDIO_IRQHandler,               /* pos 48 */
    (uintptr_t)TIM5_IRQHandler,               /* pos 49 */
    (uintptr_t)SPI3_IRQHandler,               /* pos 50 */
    0,                                        /* pos 51 reserved */
    0,                                        /* pos 52 reserved */
    0,                                        /* pos 53 reserved */
    0,                                        /* pos 54 reserved */
    (uintptr_t)DMA2_Stream0_IRQHandler,       /* pos 55 */
    (uintptr_t)DMA2_Stream1_IRQHandler,       /* pos 56 */
    (uintptr_t)DMA2_Stream2_IRQHandler,       /* pos 57 */
    (uintptr_t)DMA2_Stream3_IRQHandler,       /* pos 58 */
    (uintptr_t)DMA2_Stream4_IRQHandler,       /* pos 59 */
    0,                                        /* pos 60 reserved */
    0,                                        /* pos 61 reserved */
    0,                                        /* pos 62 reserved */
    0,                                        /* pos 63 reserved */
    0,                                        /* pos 64 reserved */
    0,                                        /* pos 65 reserved */
    (uintptr_t)OTG_FS_IRQHandler,             /* pos 66 */
    (uintptr_t)DMA2_Stream5_IRQHandler,       /* pos 67 */
    (uintptr_t)DMA2_Stream6_IRQHandler,       /* pos 68 */
    (uintptr_t)DMA2_Stream7_IRQHandler,       /* pos 69 */
    (uintptr_t)USART6_IRQHandler,             /* pos 70 */
    (uintptr_t)I2C3_EV_IRQHandler,            /* pos 71 */
    (uintptr_t)I2C3_ER_IRQHandler,            /* pos 72 */
    0,                                        /* pos 73 reserved */
    0,                                        /* pos 74 reserved */
    0,                                        /* pos 75 reserved */
    0,                                        /* pos 76 reserved */
    0,                                        /* pos 77 reserved */
    0,                                        /* pos 78 reserved */
    0,                                        /* pos 79 reserved */
    (uintptr_t)FPU_IRQHandler,                /* pos 80 */
    0,                                        /* pos 81 reserved */
    0,                                        /* pos 82 reserved */
    (uintptr_t)SPI4_IRQHandler,               /* pos 83 */
};

void Reset_Handler(void) {
  /* copy data section */
  size_t data_size = (size_t)&_edata - (size_t)&_sdata;
  memcpy(&_sdata, &_sidata, data_size);
  /* clear bss section */
  size_t bss_size = (size_t)&_ebss - (size_t)&_sbss;
  memset(&_sbss, 0, bss_size);
  /* call main function */
  main();
  while (1) {
    /* hang out if exist main */
  }
}

void Default_Handler(void) {
  while (1) {
    /* default handler just hang out for now */
  }
}