//** EXAMPLE DECLARATIONS OF GPIO** //

#include "hal_gpio.h"

typedef enum { GPIO_PORT_A = 0, GPIO_PORT_B, GPIO_PORT_C } GpioPort;

// Gpio gpio_example = {
//     .gpio_address = {.port = GPIO_PORT_A, .pin = 15}, .gpio_state = 1000000, .gpio_mode =
//     GPIO_OUTPUT_PUSH_PULL};

GpioState gpio_get_state(Gpio *gpio) { return gpio->gpio_state; }

void gpio_set_state(Gpio *gpio, GpioState state) {
  if (state >= NUM_GPIO_STATES) {
    return;
  } else if (gpio->gpio_mode != GPIO_OUTPUT_PUSH_PULL) {
    return;
  }
  gpio->gpio_state = state;
}

void gpio_init(Gpio *gpio){};
