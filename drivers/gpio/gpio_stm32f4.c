#include "gpio.h"
#include "stm32f4.h"
#include <stddef.h>
#include <stdint.h>

int gpio_enable(gpio_port_t port) {
  switch (port) {
  case GPIO_PORT_A:
    RCC->AHB1ENR |= GPIO_A_ENABLE_MASK;
    return 0;
  case GPIO_PORT_B:
    RCC->AHB1ENR |= GPIO_B_ENABLE_MASK;
    return 0;
  case GPIO_PORT_C:
    RCC->AHB1ENR |= GPIO_C_ENABLE_MASK;
    return 0;
  case GPIO_PORT_D:
    RCC->AHB1ENR |= GPIO_D_ENABLE_MASK;
    return 0;

  default:
    return -1;
  }
}

static GPIO_TypeDef *get_gpio_reg(gpio_port_t port) {
  switch (port) {
  case GPIO_PORT_A:
    return GPIO_A;
  case GPIO_PORT_B:
    return GPIO_B;
  case GPIO_PORT_C:
    return GPIO_C;
  case GPIO_PORT_D:
    return GPIO_D;

  default:
    return NULL;
  }
}

int gpio_set(gpio_port_t port, uint16_t mask) {
  GPIO_TypeDef *gpio_typedef_x = get_gpio_reg(port);
  if (gpio_typedef_x == NULL)
    return -1;
  gpio_typedef_x->ODR |= mask;
  return 0;
}

int gpio_clear(gpio_port_t port, uint16_t mask) {
  GPIO_TypeDef *gpio_typedef_x = get_gpio_reg(port);
  if (gpio_typedef_x == NULL)
    return -1;
  gpio_typedef_x->ODR &= ~mask;
  return 0;
}

int gpio_toggle(gpio_port_t port, uint16_t mask) {
  GPIO_TypeDef *gpio_typedef_x = get_gpio_reg(port);
  if (gpio_typedef_x == NULL)
    return -1;
  gpio_typedef_x->ODR ^= mask;
  return 0;
}

uint16_t gpio_read(gpio_port_t port) {
  GPIO_TypeDef *gpio_typedef_x = get_gpio_reg(port);
  if (gpio_typedef_x == NULL)
    return 0;
  return (uint16_t)gpio_typedef_x->IDR;
}

int gpio_config_pin(gpio_port_t port, gpio_config_t config, uint16_t pin_num) {
  if (pin_num > 15) {
    return -1;
  }
  GPIO_TypeDef *gpio_typedef_x = get_gpio_reg(port);
  if (gpio_typedef_x == NULL)
    return -1;

  /* 1. Configure MODER (2 bits per pin) */
  uint32_t moder_val = 0;
  switch (config.mode) {
  case GPIO_MODE_INPUT:
    moder_val = 0b00;
    break;
  case GPIO_MODE_OUTPUT_PP:
  case GPIO_MODE_OUTPUT_OD:
    moder_val = 0b01;
    break;
  case GPIO_MODE_AF_PP:
  case GPIO_MODE_AF_OD:
    moder_val = 0b10;
    break;
  case GPIO_MODE_ANALOG:
    moder_val = 0b11;
    break;
  }
  gpio_typedef_x->MODER &= ~(0b11U << (pin_num * 2));
  gpio_typedef_x->MODER |= (moder_val << (pin_num * 2));

  /* 2. Configure OTYPER (1 bit per pin: 0 = Push-Pull, 1 = Open-Drain) */
  uint32_t otyper_val = 0;
  if (config.mode == GPIO_MODE_OUTPUT_OD || config.mode == GPIO_MODE_AF_OD) {
    otyper_val = 1;
  }
  gpio_typedef_x->OTYPER &= ~(1U << pin_num);
  gpio_typedef_x->OTYPER |= (otyper_val << pin_num);

  /* 3. Configure OSPEEDR (2 bits per pin) */
  uint32_t speed_val = 0;
  switch (config.speed) {
  case GPIO_SPEED_LOW:
    speed_val = 0b00;
    break;
  case GPIO_SPEED_MEDIUM:
    speed_val = 0b01;
    break;
  case GPIO_SPEED_HIGH:
    speed_val = 0b10; /* High speed */
    break;
  }
  gpio_typedef_x->OSPEEDR &= ~(0b11U << (pin_num * 2));
  gpio_typedef_x->OSPEEDR |= (speed_val << (pin_num * 2));

  /* 4. Configure PUPDR (2 bits per pin for pull-up/pull-down) */
  uint32_t pull_val = 0;
  switch (config.pull) {
  case GPIO_PULL_NONE:
    pull_val = 0b00;
    break;
  case GPIO_PULL_UP:
    pull_val = 0b01;
    break;
  case GPIO_PULL_DOWN:
    pull_val = 0b10;
    break;
  }
  gpio_typedef_x->PUPDR &= ~(0b11U << (pin_num * 2));
  gpio_typedef_x->PUPDR |= (pull_val << (pin_num * 2));

  return 0;
}