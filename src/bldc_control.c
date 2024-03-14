#include "bldc_control.h"

static void prv_bldc_zcross_detection() {
    // Implement logic to detect when the back-EMF crosses zero
    // This may involve comparing the current and previous back-EMF values
    // and checking for a change in sign.
}

// User must define phaseA/phaseB/phaseC pins + timer
void bldc_6step_init() {
    PhaseConfig_t phaseA = {.in_a =, .sd_a =, zcross_a =, .pwm_a = };
    PhaseConfig_t phaseB;
    PhaseConfig_t phaseC;

    gpio_set_state(&phaseA.sd_a, GPIO_STATE_HIGH);
}

void run_bldc_6step() {}

void bldc_6step_commutation() {
    switch (currentRotorPosition) {
        case Position_1:
            Activate_Phase_U();
            Deactivate_Phase_W();
            break;
        case Position_2:
            Activate_Phase_U();
            Deactivate_Phase_V();
            break;
            // ... Repeat for all six rotor positions
    }
}