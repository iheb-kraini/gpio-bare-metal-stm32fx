#include "gpio.h"
#include "stm32f1.h"
#include <stddef.h>
#include <stdint.h>
int gpio_enable(gpio_port_t port) {
  switch (port) {
  case GPIO_PORT_A:
    RCC->APB2ENR |= GPIO_A_ENABLE_MASK;
    return 0;
    break;
  case GPIO_PORT_B:
    RCC->APB2ENR |= GPIO_B_ENABLE_MASK;
    return 0;
    break;
  case GPIO_PORT_C:
    RCC->APB2ENR |= GPIO_C_ENABLE_MASK;
    return 0;
    break;
  case GPIO_PORT_D:
    RCC->APB2ENR |= GPIO_D_ENABLE_MASK;
    return 0;
    break;

  default:
    return -1;
    break;
  }
}
static GPIO_TypeDef *get_gpio_reg(gpio_port_t port) {
  switch (port) {
  case GPIO_PORT_A:
    return GPIO_A;
    break;
  case GPIO_PORT_B:
    return GPIO_B;
    break;
  case GPIO_PORT_C:
    return GPIO_C;
    break;
  case GPIO_PORT_D:
    return GPIO_D;
    break;

  default:
    return NULL;
    break;
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

static uint32_t get_gpio_config_mask(gpio_config_t config) {
  uint32_t mask = 0;
  if (config.mode == GPIO_MODE_ANALOG) {
    return mask;
  }
  if (config.mode == GPIO_MODE_INPUT) {
    switch (config.pull) {
    case GPIO_PULL_NONE:
      mask = 0b00000100;
      break;
    case GPIO_PULL_DOWN:
      mask = 0b00001000;
      break;
    case GPIO_PULL_UP:
      mask = 0b00001000;
      break;

    default:
      break;
    }
    return mask;
  }
  switch (config.speed) {
  case GPIO_SPEED_LOW:
    mask |= 0b00000010;
    break;
  case GPIO_SPEED_MEDIUM:
    mask |= 0b00000001;
    break;
  case GPIO_SPEED_HIGH:
    mask |= 0b00000011;
    break;
  }

  switch (config.mode) {
  case GPIO_MODE_OUTPUT_PP:
    mask |= 0b00000000;
    break;
  case GPIO_MODE_OUTPUT_OD:
    mask |= 0b00000100;
    break;
  case GPIO_MODE_AF_PP:
    mask |= 0b00001000;
    break;
  case GPIO_MODE_AF_OD:
    mask |= 0b00001100;
    break;
  default:
    break;
  }

  return mask;
}

int gpio_config_pin(gpio_port_t port, gpio_config_t config, uint16_t pin_num) {
  if (pin_num > 15) {
    return -1;
  }
  GPIO_TypeDef *gpio_typedef_x = get_gpio_reg(port);
  if (gpio_typedef_x == NULL)
    return -1;
  uint32_t mask = get_gpio_config_mask(config);
  volatile uint32_t *gpio_config_reg =
      (pin_num < 8) ? &gpio_typedef_x->CRL : &gpio_typedef_x->CRH;
  *gpio_config_reg &= ~(0b00001111U << (pin_num % 8) * 4);
  *gpio_config_reg |= mask << (pin_num % 8) * 4;
  if ((config.mode == GPIO_MODE_INPUT || config.mode == GPIO_MODE_ANALOG) &&
      config.pull != GPIO_PULL_NONE) {
    if (config.pull == GPIO_PULL_UP)
      gpio_typedef_x->ODR |= 1U << pin_num;
    gpio_typedef_x->ODR &= ~(1U << pin_num);
  }

  return 0;
}