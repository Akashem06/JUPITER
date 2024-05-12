#ifndef MOCK_CLOCK_HPP
#define MOCK_CLOCK_HPP

#include "gmock/gmock.h"
#include "motor_phase.hpp"

namespace HW {

class MOCK_MotorPhase : public MotorPhase {
    public:
        MOCK_METHOD(JupiterStatus, init, (bool hall_sense_enabled), (override));
        MOCK_METHOD(JupiterStatus, set_phase, (const phase_cmd& a, const phase_cmd& b, const phase_cmd& c), (override));
        MOCK_METHOD(JupiterStatus, read_hall_sensors, (hall_sense& hall_sense), (override));
        MOCK_METHOD(JupiterStatus, read_phase_voltage, (phase_voltage& phase_voltage), (override));
        MOCK_METHOD(JupiterStatus, read_phase_current, (phase_current& current), (override));
        MOCK_METHOD(JupiterStatus, read_bus_voltage, (float& bus_voltage), (override));
};

}

#endif