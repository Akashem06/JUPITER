#ifndef PWM_H
#define PWM_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Wrapper function that initalizes the PWM timer interfaces
 */
void pwm_init();

/**
 * @brief Inverts phases of the motor to go reverse
 */
void invert_phases(bool inverted);

/**
 * @brief Sets the duty cycle of the PWM signal for Phase A
 * @param duty_value the duty cycle value
 * @param enableOutput true to enable the output, false to disable the half
 * bridge
 */
void set_phaseA_duty(uint32_t duty_value, bool enable);

/**
 * @brief Sets the duty cycle of the PWM signal for Phase B
 * @param duty_value the duty cycle value
 * @param enableOutput true to enable the output, false to disable the half
 * bridge
 */
void set_phaseB_duty(uint32_t duty_value, bool enable);

/**
 * @brief Sets the duty cycle of the PWM signal for Phase C
 * @param duty_value the duty cycle value
 * @param enableOutput true to enable the output, false to disable the half
 * bridge
 */
void set_phaseC_duty(uint32_t duty_value, bool enable);

#endif