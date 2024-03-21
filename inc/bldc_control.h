#ifndef BLDC_CONTROL_H
#define BLDC_CONTROL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "hal_gpio.h"
#include "hal_tim.h"
#include "status.h"

typedef enum { PHASE_A = 0, PHASE_B, PHASE_C } PhaseIndex;

// config class
typedef struct {
  uint16_t speed;
  bool reversed;
  struct {
    Gpio in;
    Gpio sd;  // Shutdown pin. Enabled low
    Gpio zcross;
    Timer pwm;
  } phase_A;
  struct {
    Gpio in;
    Gpio sd;  // Shutdown pin. Enabled low
    Gpio zcross;
    Timer pwm;
  } phase_B;
  struct {
    Gpio in;
    Gpio sd;  // Shutdown pin. Enabled low
    Gpio zcross;
    Timer pwm;
  } phase_C;
} PhaseConfig_t;

/**
 * @brief Initialize motor config
 */
JupiterStatus bldc_6step_init(uint16_t speed, PhaseConfig_t *user_config);

/**
 * @brief Main control loop
 */
JupiterStatus run_bldc_6step(void);

/**
 * @brief Determines which magnetes to trigger depending on back EMF and zero-crossing detection
 */
JupiterStatus set_bldc_6step_speed(uint16_t speed);

#endif