//** EXAMPLE DECLARATIONS OF GPIO** //

#include "hal_gpio.h"

typedef enum { GPIO_PORT_A = 0, GPIO_PORT_B, GPIO_PORT_C } GpioPort;

typedef struct {
    GpioAddress gpio_address;
    GpioState gpio_state;
    GpioMode gpio_mode;
} GpioExample_t;

GpioExample_t gpio_example = {
    .gpio_address = {.port = GPIO_PORT_A, .pin = 15}, .gpio_state = 1000000, .gpio_mode = GPIO_OUTPUT_PUSH_PULL};

GpioState gpio_get_state_example(Gpio *gpio) { return gpio->gpio_state; }

void gpio_init(Gpio *gpio) { gpio->gpio_get_state = gpio_get_state_example; }
