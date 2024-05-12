#ifndef SIX_STEP_HPP
#define SIX_STEP_HPP

#include "motor_phase.hpp"
#include "math.hpp"

enum class CommutationSignal {
    HIGH,           // The phase's DC voltage is set to high
    LOW,            // The phase's DC voltage is set to low
    HI_Z_RISING,    // The phase is set to high-Z (disconnected) and the voltage is rising (used for zero crossing detection)
    HI_Z_FALLING,   // The phase is set to high-Z (disconnected) and the voltage is falling (used for zero crossing detection)
};

typedef struct {
    /** List of phase commutation signal */
    CommutationSignal signals[HW::MotorPhase::NUM_PHASES];
} commutation_step;

constexpr uint8_t num_commutation_steps = 6;

/**
 * @brief Back EMF Voltage + Signal representation of each phases
*/
constexpr commutation_step commutation_steps[num_commutation_steps] = {
    {CommutationSignal::HIGH, CommutationSignal::LOW, CommutationSignal::HI_Z_FALLING},
    {CommutationSignal::HIGH, CommutationSignal::HI_Z_RISING, CommutationSignal::LOW},
    {CommutationSignal::HI_Z_FALLING, CommutationSignal::HIGH, CommutationSignal::LOW},
    {CommutationSignal::LOW, CommutationSignal::HIGH, CommutationSignal::HI_Z_RISING},
    {CommutationSignal::LOW, CommutationSignal::HI_Z_FALLING, CommutationSignal::HIGH},
    {CommutationSignal::HI_Z_RISING, CommutationSignal::LOW, CommutationSignal::HIGH},
};

class BLDC6StepControl {
    private:
        HW::MotorPhase& motor;
        HW::MotorPhase::phase_cmd phase_command[HW::MotorPhase::NUM_PHASES];

    public:
        explicit BLDC6StepControl(HW::MotorPhase& motor) : motor(motor) {};
        virtual ~BLDC6StepControl() {}

        /**
         * @brief Run the control loop
         */
        JupiterStatus run(float motor_speed);

        /**
         * @brief Determines the commutation step based on hall sense reading
         * @param hall_sense array of hall sense readings to be filled in, a-b-c
         * @returns Correct commutation step based on hall sense array
         */
        commutation_step determine_commutation_step_from_hall_sense(HW::MotorPhase::hall_sense hall_sense);

        /**
         * @brief Generate the duty cycles for the 3 phases based on the commutation step
         * @param phase_command array of phase commands to be filled in, a-b-c
         * @param commutation_step the commutation step to generate the duty cycles for
         * @param motor_speed the motor speed to generate the duty cycles for. 0 - 1.0f
         */
        void determine_inverter_duty_cycles(HW::MotorPhase::phase_cmd phase_command[3],
                                                commutation_step current_commutation_step, float motor_speed);
};

#endif