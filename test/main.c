#include "bldc_control.h"
#include "hal_gpio.h"
#include "hal_tim.h"

typedef enum { GPIO_PORT_A = 0, GPIO_PORT_B, GPIO_PORT_C } GpioPort;

static const Gpio phaseA_in = {.gpio_address = {.port = GPIO_PORT_A, .pin = 8},
                               .gpio_mode = GPIO_OUTPUT_PUSH_PULL,
                               .gpio_state = GPIO_STATE_LOW};

static const Gpio phaseA_zcross = {.gpio_address = {.port = GPIO_PORT_A, .pin = 0},
                                   .gpio_mode = GPIO_INPUT_PULL_DOWN,
                                   .gpio_state = GPIO_STATE_LOW};

static const Gpio phaseB_in = {.gpio_address = {.port = GPIO_PORT_A, .pin = 9},
                               .gpio_mode = GPIO_OUTPUT_PUSH_PULL,
                               .gpio_state = GPIO_STATE_LOW};

static const Gpio phaseB_zcross = {.gpio_address = {.port = GPIO_PORT_A, .pin = 1},
                                   .gpio_mode = GPIO_INPUT_PULL_DOWN,
                                   .gpio_state = GPIO_STATE_LOW};

static const Gpio phaseC_in = {.gpio_address = {.port = GPIO_PORT_A, .pin = 10},
                               .gpio_mode = GPIO_OUTPUT_PUSH_PULL,
                               .gpio_state = GPIO_STATE_LOW};

static const Gpio phaseC_zcross = {.gpio_address = {.port = GPIO_PORT_A, .pin = 2},
                                   .gpio_mode = GPIO_INPUT_PULL_DOWN,
                                   .gpio_state = GPIO_STATE_LOW};

PhaseConfig_t phase_config = {.speed = 30,
                              .reversed = false,
                              .phase_A = {.in = phaseA_in, .zcross = phaseA_zcross},
                              .phase_B = {.in = phaseB_in, .zcross = phaseB_zcross},
                              .phase_C = {
                                  .in = phaseC_in,
                                  .zcross = phaseC_zcross,
                              }};

int main(void) { return 0; }
