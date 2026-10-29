#ifndef STM32F401CB_HEADER
#define STM32F401CB_HEADER

#include <stdint.h>

typedef struct {
  volatile uint32_t CR;       /* 0x00 */
  volatile uint32_t PLLCFGR;  /* 0x04 */
  volatile uint32_t CFGR;     /* 0x08 */
  volatile uint32_t CIR;      /* 0x0C */
  volatile uint32_t AHB1RSTR; /* 0x10 */
  volatile uint32_t AHB2RSTR; /* 0x14 */
  uint32_t RESERVED0[2];      /* 0x18-0x1C */
  volatile uint32_t APB1RSTR; /* 0x20 */
  volatile uint32_t APB2RSTR; /* 0x24 */
  uint32_t RESERVED1[2];      /* 0x28-0x2C */
  volatile uint32_t AHB1ENR;  /* 0x30 */
  volatile uint32_t AHB2ENR;  /* 0x34 */
  uint32_t RESERVED2[2];      /* 0x38-0x3C */
  volatile uint32_t APB1ENR;  /* 0x40 */
  volatile uint32_t APB2ENR;  /* 0x44 */
} RCC_TypeDef;

#define RCC_BASE 0x40023800U
#define RCC ((RCC_TypeDef *)RCC_BASE)

typedef struct {
  volatile uint32_t MODER;   /* 0x00 - Mode register */
  volatile uint32_t OTYPER;  /* 0x04 - Output type register */
  volatile uint32_t OSPEEDR; /* 0x08 - Output speed register */
  volatile uint32_t PUPDR;   /* 0x0C - Pull-up/pull-down register */
  volatile uint32_t IDR;     /* 0x10 - Input data register */
  volatile uint32_t ODR;     /* 0x14 - Output data register */
  volatile uint32_t BSRR;    /* 0x18 - Bit set/reset register */
  volatile uint32_t LCKR;    /* 0x1C - Configuration lock register */
  volatile uint32_t
      AFR[2]; /* 0x20-0x24 - Alternate function registers (AFRL, AFRH) */
} GPIO_TypeDef;

#define GPIO_A_BASE 0x40020000U
#define GPIO_B_BASE 0x40020400U
#define GPIO_C_BASE 0x40020800U
#define GPIO_D_BASE 0x40020C00U

#define GPIO_A ((GPIO_TypeDef *)GPIO_A_BASE)
#define GPIO_B ((GPIO_TypeDef *)GPIO_B_BASE)
#define GPIO_C ((GPIO_TypeDef *)GPIO_C_BASE)
#define GPIO_D ((GPIO_TypeDef *)GPIO_D_BASE)

/* On STM32F4, GPIO clocks are enabled via AHB1ENR */
#define GPIO_A_ENABLE_MASK (1U << 0)
#define GPIO_B_ENABLE_MASK (1U << 1)
#define GPIO_C_ENABLE_MASK (1U << 2)
#define GPIO_D_ENABLE_MASK (1U << 3)

#endif