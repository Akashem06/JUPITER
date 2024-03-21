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
  zeroCrossings[0] = gpio_get_state(&phase_config->phase_A.zcross);
  zeroCrossings[1] = gpio_get_state(&phase_config->phase_B.zcross);
  zeroCrossings[2] = gpio_get_state(&phase_config->phase_C.zcross);
}

static int prv_get_commutation_step(int zeroCrossings[]) {
  if (zeroCrossings[0] && !zeroCrossings[1]) {
        return 0; // A+ (HIGH) B- (LOW)
    } else if (zeroCrossings[1] && !zeroCrossings[2]) {
        return 1; // A+ (HIGH) C- (LOW)
    } else if (zeroCrossings[2] && !zeroCrossings[3]) {
        return 2; // B+ (HIGH) C- (LOW)
    } else if (zeroCrossings[3] && !zeroCrossings[4]) {
        return 3; // B+ (HIGH) A- (LOW)
    } else if (zeroCrossings[4] && !zeroCrossings[5]) {
        return 4; // C+ (HIGH) A- (LOW)
    } else if (zeroCrossings[5] && !zeroCrossings[0]) {
        return 5; // C+ (HIGH) B- (LOW)
    } else {
        return -1; // Invalid or unknown state
    }
}

// Placeholder for commutating motor phases
static void prv_commutate_motor(int commutationStep) {
  switch (commutationStep) {
      case 0:
        // A+ (HIGH) B- (LOW)
        gpio_set_state(&phase_config->phase_C.sd, GPIO_STATE_LOW);
        gpio_set_state(&phase_config->phase_A.sd, GPIO_STATE_HIGH);

        gpio_set_state(&phase_config->phase_A.in, GPIO_STATE_HIGH);
        gpio_set_state(&phase_config->phase_B.in, GPIO_STATE_LOW);

        break;

      case 1:
        // A+ (HIGH) C- (LOW)
        gpio_set_state(&phase_config->phase_B.sd, GPIO_STATE_LOW);
        gpio_set_state(&phase_config->phase_C.sd, GPIO_STATE_HIGH);

        gpio_set_state(&phase_config->phase_A.in, GPIO_STATE_HIGH);
        gpio_set_state(&phase_config->phase_C.in, GPIO_STATE_LOW);

        break;

      case 2:
        // B+ (HIGH) C- (LOW)
        gpio_set_state(&phase_config->phase_A.sd, GPIO_STATE_LOW);
        gpio_set_state(&phase_config->phase_B.sd, GPIO_STATE_HIGH);
        
        gpio_set_state(&phase_config->phase_B.in, GPIO_STATE_HIGH);
        gpio_set_state(&phase_config->phase_C.sd, GPIO_STATE_LOW);
        break;

      case 3:
        // B+ (HIGH) A- (LOW)
        gpio_set_state(&phase_config->phase_C.sd, GPIO_STATE_LOW);
        gpio_set_state(&phase_config->phase_A.sd, GPIO_STATE_HIGH);

        gpio_set_state(&phase_config->phase_B.sd, GPIO_STATE_LOW);
        gpio_set_state(&phase_config->phase_A.in, GPIO_STATE_HIGH);
        break;

      case 4:
        // C+ (HIGH) A- (LOW)
        gpio_set_state(&phase_config->phase_B.sd, GPIO_STATE_LOW);
        gpio_set_state(&phase_config->phase_C.sd, GPIO_STATE_HIGH);

        gpio_set_state(&phase_config->phase_C.in, GPIO_STATE_HIGH);
        gpio_set_state(&phase_config->phase_A.in, GPIO_STATE_LOW);
        break;
        
      case 5:
        // C+ (HIGH) B- (LOW)
        gpio_set_state(&phase_config->phase_A.sd, GPIO_STATE_LOW);
        gpio_set_state(&phase_config->phase_B.sd, GPIO_STATE_HIGH);

        gpio_set_state(&phase_config->phase_C.in, GPIO_STATE_HIGH);
        gpio_set_state(&phase_config->phase_B.in, GPIO_STATE_LOW);
        break;

      default:
        // ERROR
        break;
  }
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
  int zeroCrossings[3];
  prv_zero_crossing(zeroCrossings);

  int commutationStep = prv_get_commutation_step(zeroCrossings);

  prv_commutate_motor(commutationStep);

  // Implement safety features (e.g., overcurrent protection)

  // Delay to control commutation frequency
  // delay(COMMUTATION_PERIOD);  // Adjust with the desired commutation period
  return JUPITER_OK;
}
