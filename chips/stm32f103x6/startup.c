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

/* ---- Peripheral interrupts (F103x6 set) ---- */
void WWDG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TAMPER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel2_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel3_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel4_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel5_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel6_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel7_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void ADC1_2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USB_HP_CAN1_TX_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void USB_LP_CAN1_RX0_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void CAN1_RX1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN1_SCE_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USBWakeUp_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));

/* ---- Vector table ---- */
__attribute__((section(".isr_vector"), used)) const uintptr_t vector_table[] = {
    (uintptr_t)&_estack,           /* 0  initial SP        */
    (uintptr_t)Reset_Handler,      /* 1  Reset             */
    (uintptr_t)NMI_Handler,        /* 2  NMI               */
    (uintptr_t)HardFault_Handler,  /* 3  HardFault         */
    (uintptr_t)MemManage_Handler,  /* 4  MemManage         */
    (uintptr_t)BusFault_Handler,   /* 5  BusFault          */
    (uintptr_t)UsageFault_Handler, /* 6  UsageFault        */
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
    (uintptr_t)WWDG_IRQHandler,            /* pos 0  */
    (uintptr_t)PVD_IRQHandler,             /* pos 1  */
    (uintptr_t)TAMPER_IRQHandler,          /* pos 2  */
    (uintptr_t)RTC_IRQHandler,             /* pos 3  */
    (uintptr_t)FLASH_IRQHandler,           /* pos 4  */
    (uintptr_t)RCC_IRQHandler,             /* pos 5  */
    (uintptr_t)EXTI0_IRQHandler,           /* pos 6  */
    (uintptr_t)EXTI1_IRQHandler,           /* pos 7  */
    (uintptr_t)EXTI2_IRQHandler,           /* pos 8  */
    (uintptr_t)EXTI3_IRQHandler,           /* pos 9  */
    (uintptr_t)EXTI4_IRQHandler,           /* pos 10 */
    (uintptr_t)DMA1_Channel1_IRQHandler,   /* pos 11 */
    (uintptr_t)DMA1_Channel2_IRQHandler,   /* pos 12 */
    (uintptr_t)DMA1_Channel3_IRQHandler,   /* pos 13 */
    (uintptr_t)DMA1_Channel4_IRQHandler,   /* pos 14 */
    (uintptr_t)DMA1_Channel5_IRQHandler,   /* pos 15 */
    (uintptr_t)DMA1_Channel6_IRQHandler,   /* pos 16 */
    (uintptr_t)DMA1_Channel7_IRQHandler,   /* pos 17 */
    (uintptr_t)ADC1_2_IRQHandler,          /* pos 18 */
    (uintptr_t)USB_HP_CAN1_TX_IRQHandler,  /* pos 19 */
    (uintptr_t)USB_LP_CAN1_RX0_IRQHandler, /* pos 20 */
    (uintptr_t)CAN1_RX1_IRQHandler,        /* pos 21 */
    (uintptr_t)CAN1_SCE_IRQHandler,        /* pos 22 */
    (uintptr_t)EXTI9_5_IRQHandler,         /* pos 23 */
    (uintptr_t)TIM1_BRK_IRQHandler,        /* pos 24 */
    (uintptr_t)TIM1_UP_IRQHandler,         /* pos 25 */
    (uintptr_t)TIM1_TRG_COM_IRQHandler,    /* pos 26 */
    (uintptr_t)TIM1_CC_IRQHandler,         /* pos 27 */
    (uintptr_t)TIM2_IRQHandler,            /* pos 28 */
    (uintptr_t)TIM3_IRQHandler,            /* pos 29 */
    0,                                     /* pos 30 reserved (no TIM4) */
    (uintptr_t)I2C1_EV_IRQHandler,         /* pos 31 */
    (uintptr_t)I2C1_ER_IRQHandler,         /* pos 32 */
    0,
    0,                               /* pos 33-34 reserved (no I2C2) */
    (uintptr_t)SPI1_IRQHandler,      /* pos 35 */
    0,                               /* pos 36 reserved (no SPI2) */
    (uintptr_t)USART1_IRQHandler,    /* pos 37 */
    (uintptr_t)USART2_IRQHandler,    /* pos 38 */
    0,                               /* pos 39 reserved (no USART3) */
    (uintptr_t)EXTI15_10_IRQHandler, /* pos 40 */
    (uintptr_t)RTC_Alarm_IRQHandler, /* pos 41 */
    (uintptr_t)USBWakeUp_IRQHandler, /* pos 42 */
};

/* TODO : Default_Handler, Reset_Handler */

void Reset_Handler(void) {
  // copy data section
  size_t data_size = (size_t)&_edata - (size_t)&_sdata;
  memcpy(&_sdata, &_sidata, data_size);
  // clear bss section
  size_t bss_size = (size_t)&_ebss - (size_t)&_sbss;
  memset(&_sbss, 0, bss_size);
  // call main function
  main();
  while (1) {
    // hang out if exist main
  }
}
void Default_Handler(void) {
  while (1) {
    // default handler just hang out for now
  }
}
