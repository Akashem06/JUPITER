#include "bldc_control.h"

// Define commutation table representing the commutation sequence
static const int commutation_table[6][3] = {
  { PHASE_A, PHASE_B, PHASE_C },  // Step 1
  { PHASE_B, PHASE_A, PHASE_C },  // Step 2
  { PHASE_B, PHASE_C, PHASE_A },  // Step 3
  { PHASE_C, PHASE_B, PHASE_A },  // Step 4
  { PHASE_C, PHASE_A, PHASE_B },  // Step 5
  { PHASE_A, PHASE_C, PHASE_B }   // Step 6
};

static PhaseConfig_t *phase_config;

JupiterStatus bldc_6step_init(uint16_t speed, PhaseConfig_t *user_config) {
  if (user_config == NULL) {
    return JUPITER_INVALID_ARGS;
  }
  phase_config = user_config;
  return JUPITER_OK;
}

// Future expansion
// static void prv_read_voltages(int phaseVoltages[]) {}

// Zero crossing detection
static void prv_zero_crossing(int zeroCrossings[]) {
  gpio_get_state(&phase_config->phase_A.zcross);
  gpio_get_state(&phase_config->phase_B.zcross);
  gpio_get_state(&phase_config->phase_C.zcross);
}

static int prv_get_commutation_step(int zeroCrossings[]) { return 0; }

// Placeholder for commutating motor phases
static void prv_commutate_motor(int commutationStep) {
  // Commutate motor phases based on the determined step
  // Example:
  // switch (commutationStep) {
  //     case 0:
  //         // Commutate phase A high, phase B low, phase C off
  //         HAL_GPIO_WritePin(PHASE_A_GPIO_Port, PHASE_A_Pin, GPIO_PIN_SET);
  //         HAL_GPIO_WritePin(PHASE_B_GPIO_Port, PHASE_B_Pin, GPIO_PIN_RESET);
  //         HAL_GPIO_WritePin(PHASE_C_GPIO_Port, PHASE_C_Pin, GPIO_PIN_RESET);
  //         break;
  //     // Other commutation steps...
  // }
}

JupiterStatus set_bldc_6step_speed(uint16_t updated_speed) {
  phase_config->speed = updated_speed;
  // Adjust motor speed as required
  // Example:
  // setMotorSpeed(speed); // Adjust PWM duty cycle based on speed value
  return JUPITER_OK;
}

// Placeholder for implementing delay
void delay(int milliseconds) {
  // Implement delay for a specified duration using HAL library
  // Example:
  // HAL_Delay(milliseconds);
}

JupiterStatus run_bldc_6step() {
  // Detect zero crossings
  int zeroCrossings[3];
  prv_zero_crossing(zeroCrossings);

  // Determine commutation step
  int commutationStep = prv_get_commutation_step(zeroCrossings);

  // Commutate motor phases
  prv_commutate_motor(commutationStep);

  // Implement safety features (e.g., overcurrent protection)

  // Delay to control commutation frequency
  // delay(COMMUTATION_PERIOD);  // Adjust with the desired commutation period
  return JUPITER_OK;
}
