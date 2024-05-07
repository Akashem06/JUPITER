#ifndef MOTOR_PHASE_HPP
#define MOTOR_PHASE_HPP

#include "status.hpp"

#include <stdint.h>

namespace HW {

class MotorPhase {
    MotorPhase(bool hall_sense_enabled) : hall_sense_enabled(hall_sense_enabled) {};
    virtual ~MotorPhase() {}

    // Sensorless / Hall_sense modes
    bool hall_sense_enabled = false;

    class phase_cmd {
        phase_cmd() = default;

        float duty_cycle = 0.0f;

        /**
         * @brief Enable the phase output
         */
        bool enable = false;

        /**
         * @brief Construct a phase command
         * @param duty_cycle Duty cycle for the high side PWM channel
         * @param enable Enable the phase output
         * @note The duty cycle is between 0.0f and 1.0f, where 0.5 is 50% duty cycle and represents 0V (assumes complementary
         */
        phase_cmd(float duty_cycle, bool enable) : duty_cycle(duty_cycle), enable(enable) {}
    };

    // Template for hall sense readings
    class hall_sense {

        public:
            hall_sense() = default;


            /**
             * @brief Gpio state of hall_sense pin
             */
            bool a = false;

            /**
             * @brief Gpio state of hall_sense pin
             */
            bool b = false;

            /**
             * @brief Gpio state of hall_sense pin
             */
            bool c = false;
    };

    class phase_voltage {
        public:
            phase_voltage() = default;
                
            float a = 0.0f;
            float b = 0.0f;
            float c = 0.0f;
    };

    class phase_current {
        public:
            phase_current() = default;
                
            float a = 0.0f;
            float b = 0.0f;
            float c = 0.0f;
    };

    /**
     * @brief Initialize the 3-phase bridge
     * @return JupiterStatus The status of the operation
     */
    virtual JupiterStatus init() = 0;

    /**
     * @brief Set the phase voltages
     * @param a The phase A voltage
     * @param b The phase B voltage
     * @param c The phase C voltage
     * @return JupiterStatus The status of the operation
     */
    virtual JupiterStatus set_phase(const phase_cmd& a, const phase_cmd& b, const phase_cmd& c) = 0;

    /**
     * @brief Read the phase voltages from the bridge
     * @param phase_voltage The phase voltages in volts
     * @return JupiterStatus The status of the operation
     */
    virtual JupiterStatus read_phase_voltage(phase_voltage& phase_voltage) = 0;

    /**
     * @brief Read the phase currents from the bridge
     * @param current The phase currents in amps
     * @return JupiterStatus The status of the operation
     */
    virtual JupiterStatus read_phase_current(phase_current& current) = 0;

    /**
     * @brief Read the bus voltage from the bridge
     * @param bus_voltage The bus voltage in volts
     * @return JupiterStatus The status of the operation
     */
    virtual JupiterStatus read_bus_voltage(float& bus_voltage) = 0;

    /**
     * @brief Number of phases in the bridge
     */
    static constexpr uint8_t NUM_PHASES = 3;

};

}

#endif