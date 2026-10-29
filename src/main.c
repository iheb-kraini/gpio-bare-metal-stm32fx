#include "gpio.h"

static void sleep() {
  for (uint16_t i = 0; i < 1000; i++) {
  }
}

int main(void) {
  gpio_enable(GPIO_PORT_A);
  gpio_config_t gpio_pin_a_2 = {.mode = GPIO_MODE_OUTPUT_PP,
                                .pull = GPIO_PULL_UP,
                                .speed = GPIO_SPEED_LOW};
  gpio_config_pin(GPIO_PORT_A, gpio_pin_a_2, 2);

  while (1) {
    gpio_set(GPIO_PORT_A, 0x04);
    sleep();
    gpio_clear(GPIO_PORT_A, 0x04);
    sleep();
  }

  return 0;
}