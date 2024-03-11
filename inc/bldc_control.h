#ifndef BLDC_CONTROL_H
#define BLDC_CONTROL_H

#include <stdbool.h>
#include <stdint.h>

typedef enum { PHASE_A = 0, PHASE_B, PHASE_C } PhaseIndex;

// config class
typedef struct {
    
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