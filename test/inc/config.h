#ifndef CONFIG_H
#define CONFIG_H

#include "bldc_control.h"
#include "hal_gpio.h"
#include "hal_tim.h"

/**
 * @brief Initialize unit test config
 */
void jupiter_test_setup(PhaseConfig_t *phase_config);

#endif