#include "6step.hpp"

#include <iostream>

commutation_step BLDC6StepControl::determine_commutation_step_from_hall_sense(HW::MotorPhase::hall_sense hall_sense) {
    commutation_step step = { CommutationSignal::LOW, CommutationSignal::LOW, CommutationSignal::LOW };
    if (hall_sense.a && hall_sense.c) {
        // 0
        step = commutation_steps[0];
    } else if (hall_sense.a && hall_sense.b) {
        // 2
        step = commutation_steps[2];
    } else if (hall_sense.b && hall_sense.c) {
        // 4
        step = commutation_steps[4];
    } else if (hall_sense.a) {
        // 1
        step = commutation_steps[1];
    } else if (hall_sense.b) {
        // 3
        step = commutation_steps[3];
    } else if (hall_sense.c) {
        // 5
        step = commutation_steps[5];
    }
    return step;
}

void BLDC6StepControl::determine_inverter_duty_cycles(HW::MotorPhase::phase_cmd phase_command[3], commutation_step current_commutation_step,
                                                      float motor_speed) {
    // Clamp the motor speed to 0f to 1.0f after first abs'ing it
    float abs_speed = fabsf(motor_speed);
    math::clamp(abs_speed, 0.0f, 1.0f);

    for (int i{0}; i < 3; i++) {
        if (current_commutation_step.signals[i] == CommutationSignal::HIGH) {
            // 0.5f is the baseline for 0V supplied to the motor, since it is complementary a high will
            // drive the hi-mosfet and a low will drive the lo-mosfet. At 50% Duty cycle high and low will
            // be driven equally, and will create 0V btwn the phase and neutral

            // Therefore we can map the duty cycles as such:
            // |   Speed   | DUTY CYCLE |
            // |    0.0    |    0.5     |
            // |    1.0    |    1.0     |

            phase_command[i].duty_cycle = (abs_speed + 1.0f) / 2.0f;
            phase_command[i].enable = true;
        } else if (current_commutation_step.signals[i] == CommutationSignal::LOW) {
            // Enabling the low-side mosfet for x-phase, setting it as ground
            phase_command[i].duty_cycle = 0.0f;
            phase_command[i].enable = true;
        } else {
            phase_command[i].duty_cycle = 0.0f;
            phase_command[i].enable = false;
        }
    }
}

JupiterStatus BLDC6StepControl::run(float motor_speed) {
    commutation_step step = { CommutationSignal::LOW, CommutationSignal::LOW, CommutationSignal::LOW };
    JupiterStatus status;
    do {
        if (motor.hall_sense_enabled) {
            HW::MotorPhase::hall_sense hall_sense;
            status = motor.read_hall_sensors(hall_sense);

            if (status != JUPITER_OK) {
                break;
            }

            step = determine_commutation_step_from_hall_sense(hall_sense);
        } else {
            HW::MotorPhase::phase_voltage phase_voltage;
            status = motor.read_phase_voltage(phase_voltage);

            if (status != JUPITER_OK) {
                break;
            }
            // TODO: Add commutation step from phase_voltage
        }

    } while (false);

    if (status != JUPITER_OK) {
        phase_command[0].duty_cycle = 0.0f;
        phase_command[1].duty_cycle = 0.0f;
        phase_command[2].duty_cycle = 0.0f;
        return status;
    }

    determine_inverter_duty_cycles(phase_command, step, motor_speed);
    motor.set_phase(phase_command[0], phase_command[1], phase_command[2]);

    return status;
}
