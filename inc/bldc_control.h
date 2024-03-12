#ifndef BLDC_CONTROL_H
#define BLDC_CONTROL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "hal_tim.h"
#include "hal_gpio.h"

typedef enum { PHASE_A = 0, PHASE_B, PHASE_C } PhaseIndex;

// config class
typedef struct {
    union {
        struct {
            Gpio in_a;
            Gpio sd_a;      // Shutdown pin. Enabled low
            Gpio zcross_a;
            Timer pwm_a;
        } phase_A;
        struct {
            Gpio in_b;
            Gpio sd_b;      // Shutdown pin. Enabled low
            Gpio zcross_b;
            Timer pwm_b;
        } phase_B;
        struct {
            Gpio in_c;
            Gpio sd_c;      // Shutdown pin. Enabled low
            Gpio zcross_c;
            Timer pwm_c;
        } phase_C;
    };
} PhaseConfig_t;

/**
 * @brief Initialize motor config
 */
void bldc_6step_init(void);

/**
 * @brief Main control loop
 */
void run_bldc_6step(void);

/**
 * @brief Determines which magnetes to trigger depending on back EMF and zero-crossing detection
 */
void bldc_6step_commutation(void);

#endif