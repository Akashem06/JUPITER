#ifndef BLDC_CONTROL_PRV_H
#define BLDC_CONTROL_PRV_H

#include "bldc_control.h"

/**
 * @brief Reads zero-crossing pins
 */
void prv_zero_crossing(uint8_t zeroCrossings[]);

/**
 * @brief Determines commutation step based on zero-crossing
 */
uint8_t prv_get_commutation_step(const uint8_t zeroCrossings[]);

/**
 * @brief Commutates motor depending on the step
 */
void prv_commutate_motor(uint8_t commutationStep);

#endif
