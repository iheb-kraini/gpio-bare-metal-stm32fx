#ifndef GPIO_HEADER
#define GPIO_HEADER

#include <stdint.h>

typedef enum {
  GPIO_PORT_A,
  GPIO_PORT_B,
  GPIO_PORT_C,
  GPIO_PORT_D,
} gpio_port_t;

typedef enum {
  GPIO_MODE_INPUT,
  GPIO_MODE_OUTPUT_PP, /* push-pull */
  GPIO_MODE_OUTPUT_OD, /* open-drain */
  GPIO_MODE_AF_PP,     /* alternate function, push-pull */
  GPIO_MODE_AF_OD,
  GPIO_MODE_ANALOG,
} gpio_mode_t;

typedef enum { GPIO_PULL_NONE, GPIO_PULL_UP, GPIO_PULL_DOWN } gpio_pull_t;
typedef enum {
  GPIO_SPEED_LOW,
  GPIO_SPEED_MEDIUM,
  GPIO_SPEED_HIGH
} gpio_speed_t;

typedef struct {
  gpio_mode_t mode;
  gpio_pull_t pull;   /* only meaningful for inputs */
  gpio_speed_t speed; /* only meaningful for outputs / AF */
} gpio_config_t;

#define GPIO_PIN(n) (1U << (n))

int gpio_enable(gpio_port_t port);

/** @brief drive the selected pins high (bits set in mask, others untouched) */
int gpio_set(gpio_port_t port, uint16_t mask);

/** @brief drive the selected pins low */
int gpio_clear(gpio_port_t port, uint16_t mask);

/** @brief invert the selected pins */
int gpio_toggle(gpio_port_t port, uint16_t mask);

/** @brief read all 16 input pins of the port */
uint16_t gpio_read(gpio_port_t port);

int gpio_config_pin(gpio_port_t port, gpio_config_t config, uint16_t pin_num);

#endif