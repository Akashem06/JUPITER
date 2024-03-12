#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>

typedef enum {
    GPIO_ANALOG = 0,
    GPIO_INPUT_FLOATING,
    GPIO_INPUT_PULL_DOWN,
    GPIO_INPUT_PULL_UP,
    GPIO_OUTPUT_OPEN_DRAIN,
    GPIO_OUTPUT_PUSH_PULL,
    GPIO_ALFTN_OPEN_DRAIN,
    GPIO_ALTFN_PUSH_PULL,
    NUM_GPIO_MODES,
} GpioMode;

typedef enum { GPIO_STATE_HIGH = 0, GPIO_STATE_LOW, NUM_GPIO_STATES } GpioState;

typedef struct {
    uint8_t port;
    uint8_t pin;
} GpioAddress;

typedef struct {
    GpioState gpio_state;
    GpioState (*gpio_get_state)(GpioAddress gpio_address) void (*gpio_set_state)(GpioAddress *gpio_address)
} Gpio;

void gpio_init(Gpio *gpio){};

#endif
