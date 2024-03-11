// User-Defined Example Code

#include "hal_gpio.h"

//** EXAMPLE DECLARATIONS OF GPIO** //
typedef enum { GPIO_PORT_A = 0, GPIO_PORT_B, GPIO_PORT_C } GpioPort;

typedef struct {
    GpioAddress gpio_address;
    GpioState gpio_state;
    GpioMode gpio_mode;
    uint8_t pwm_duty_cycle;
} GpioExample_t;

GpioExample_t gpio_example = {
    .gpio_address = {.port = GPIO_PORT_A, .pin = 15}, .gpio_state = 1000000, .gpio_mode = 0xffffffff};

GpioState gpio_get_state_example(Gpio *gpio) { return gpio->gpio_state; }

void timer_init(Gpio *gpio) { gpio->gpio_get_state = gpio_get_state_example; }
