#include "config.h"

typedef enum { GPIO_PORT_A = 0, GPIO_PORT_B, GPIO_PORT_C } GpioPort;

static const Gpio phaseA_in = { .gpio_address = { .port = GPIO_PORT_A, .pin = 8 },
                                .gpio_mode = GPIO_OUTPUT_PUSH_PULL,
                                .gpio_state = GPIO_STATE_LOW };

static const Gpio phaseA_zcross = { .gpio_address = { .port = GPIO_PORT_A, .pin = 0 },
                                    .gpio_mode = GPIO_INPUT_PULL_DOWN,
                                    .gpio_state = GPIO_STATE_LOW };

static const Gpio phaseB_in = { .gpio_address = { .port = GPIO_PORT_A, .pin = 9 },
                                .gpio_mode = GPIO_OUTPUT_PUSH_PULL,
                                .gpio_state = GPIO_STATE_LOW };

static const Gpio phaseB_zcross = { .gpio_address = { .port = GPIO_PORT_A, .pin = 1 },
                                    .gpio_mode = GPIO_INPUT_PULL_DOWN,
                                    .gpio_state = GPIO_STATE_LOW };

static const Gpio phaseC_in = { .gpio_address = { .port = GPIO_PORT_A, .pin = 10 },
                                .gpio_mode = GPIO_OUTPUT_PUSH_PULL,
                                .gpio_state = GPIO_STATE_LOW };

static const Gpio phaseC_zcross = { .gpio_address = { .port = GPIO_PORT_A, .pin = 2 },
                                    .gpio_mode = GPIO_INPUT_PULL_DOWN,
                                    .gpio_state = GPIO_STATE_LOW };

void jupiter_test_setup(PhaseConfig_t *phase_config) {
    phase_config->speed = 30;
    phase_config->reversed = false;
    phase_config->phase_A.in = phaseA_in;
    phase_config->phase_A.zcross = phaseA_zcross;
    phase_config->phase_B.in = phaseB_in;
    phase_config->phase_B.zcross = phaseB_zcross;
    phase_config->phase_C.in = phaseC_in;
    phase_config->phase_C.zcross = phaseC_zcross;
}