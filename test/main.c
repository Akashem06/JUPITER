#include "bldc_control.h"
#include "hal_gpio.h"
#include "hal_tim.h"

typedef enum { GPIO_PORT_A = 0, GPIO_PORT_B, GPIO_PORT_C } GpioPort;

static const Gpio phaseA_in = {
    .gpio_address = { .port = GPIO_PORT_A, .pin = 8},
    .gpio_mode = GPIO_INPUT_PULL_DOWN,
    .gpio_state = GPIO_STATE_LOW
};

static const Gpio phaseB_in = {
    .gpio_address = { .port = GPIO_PORT_A, .pin = 9},
    .gpio_mode = GPIO_INPUT_PULL_DOWN,
    .gpio_state = GPIO_STATE_LOW
};

static const Gpio phaseC_in = {
    .gpio_address = { .port = GPIO_PORT_A, .pin = 10},
    .gpio_mode = GPIO_INPUT_PULL_DOWN,
    .gpio_state = GPIO_STATE_LOW
};

PhaseConfig_t phase_config = {
    .speed = 30,
    .reversed = false,
    .phase_A = {
        .in = phaseA_in,
    }
};

int main(void) { return 0; }
