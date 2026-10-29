#ifndef STM32F103X6_HEADER
#define STM32F103X6_HEADER

#include <stdint.h>

typedef struct {
  volatile uint32_t CR;       /* 0x00 */
  volatile uint32_t CFGR;     /* 0x04 */
  volatile uint32_t CIR;      /* 0x08 */
  volatile uint32_t APB2RSTR; /* 0x0C */
  volatile uint32_t APB1RSTR; /* 0x10 */
  volatile uint32_t AHBENR;   /* 0x14 */
  volatile uint32_t APB2ENR;  /* 0x18 */
  volatile uint32_t APB1ENR;  /* 0x1C */
  volatile uint32_t BDCR;     /* 0x20 */
  volatile uint32_t CSR;      /* 0x24 */
} RCC_TypeDef;

#define RCC_BASE 0x40021000U
#define RCC ((RCC_TypeDef *)RCC_BASE)

typedef struct {
  volatile uint32_t CRL;  // 0x00  config for low pins [0..7]
  volatile uint32_t CRH;  // 0x04 config for low pins [8..15]
  volatile uint32_t IDR;  // 0x08
  volatile uint32_t ODR;  // 0x0c
  volatile uint32_t BSRR; // 0x10
  volatile uint32_t BRR;  // 0x14
  volatile uint32_t LCKR; // 0x18
} GPIO_TypeDef;
#define GPIO_A_BASE 0x40010800U
#define GPIO_B_BASE 0x40010C00U
#define GPIO_C_BASE 0x40011000U
#define GPIO_D_BASE 0x40011400U

#define GPIO_A ((GPIO_TypeDef *)GPIO_A_BASE)
#define GPIO_B ((GPIO_TypeDef *)GPIO_B_BASE)
#define GPIO_C ((GPIO_TypeDef *)GPIO_C_BASE)
#define GPIO_D ((GPIO_TypeDef *)GPIO_D_BASE)

#define GPIO_A_ENABLE_MASK (1U << 2)
#define GPIO_B_ENABLE_MASK (1U << 3)
#define GPIO_C_ENABLE_MASK (1U << 4)
#define GPIO_D_ENABLE_MASK (1U << 5)

#endif