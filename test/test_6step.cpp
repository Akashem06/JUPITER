#include "6step.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mocks/mock_motor_phase.hpp"

#define HALL_SENSE_ENABLED 1
#define HALL_SENSE_DISABLED 0

using namespace ::testing;

void test_commutation_step(const commutation_step& commutation_step, uint8_t expected_step) {
    EXPECT_EQ(commutation_step.signals[0], commutation_steps[expected_step].signals[0]);
    EXPECT_EQ(commutation_step.signals[1], commutation_steps[expected_step].signals[1]);
    EXPECT_EQ(commutation_step.signals[2], commutation_steps[expected_step].signals[2]);
}

void set_hall_sense_readings(bool a, bool b, bool c, HW::MotorPhase::hall_sense& hall_sense) {
    hall_sense.a = a;
    hall_sense.b = b;
    hall_sense.c = c;
};

TEST(SixStepCommutation, hall_sensor_test) {
    HW::MOCK_MotorPhase mock_motor;

    EXPECT_CALL(mock_motor, init(HALL_SENSE_ENABLED)).WillOnce(Return(JUPITER_OK));
    mock_motor.init(HALL_SENSE_ENABLED);

    BLDC6StepControl six_step(mock_motor);
    HW::MotorPhase::hall_sense hall_sense;

    commutation_step step;

    // Verify that commutation step 0 outputs correct hack-emf states
    set_hall_sense_readings(1, 0, 1, hall_sense);
    step = six_step.determine_commutation_step_from_hall_sense(hall_sense);
    test_commutation_step(step, 0);

    // Verify that commutation step 1 outputs correct hack-emf states
    set_hall_sense_readings(1, 0, 0, hall_sense);
    step = six_step.determine_commutation_step_from_hall_sense(hall_sense);
    test_commutation_step(step, 1);

    // Verify that commutation step 2 outputs correct hack-emf states
    set_hall_sense_readings(1, 1, 0, hall_sense);
    step = six_step.determine_commutation_step_from_hall_sense(hall_sense);
    test_commutation_step(step, 2);

    // Verify that commutation step 3 outputs correct hack-emf states
    set_hall_sense_readings(0, 1, 0, hall_sense);
    step = six_step.determine_commutation_step_from_hall_sense(hall_sense);
    test_commutation_step(step, 3);

    // Verify that commutation step 4 outputs correct hack-emf states
    set_hall_sense_readings(0, 1, 1, hall_sense);
    step = six_step.determine_commutation_step_from_hall_sense(hall_sense);
    test_commutation_step(step, 4);

    // Verify that commutation step 5 outputs correct hack-emf states
    set_hall_sense_readings(0, 0, 1, hall_sense);
    step = six_step.determine_commutation_step_from_hall_sense(hall_sense);
    test_commutation_step(step, 5);
}

TEST(SixStepCommutation, phase_voltage_test) {}

TEST(SixStepCommutation, motor_command_test) {
    HW::MOCK_MotorPhase mock_motor;

    EXPECT_CALL(mock_motor, init(HALL_SENSE_DISABLED)).WillOnce(Return(JUPITER_OK));
    mock_motor.init(HALL_SENSE_DISABLED);

    BLDC6StepControl six_step(mock_motor);

    HW::MotorPhase::phase_cmd phase_command[HW::MotorPhase::NUM_PHASES];

    six_step.determine_inverter_duty_cycles(phase_command, commutation_steps[0], 0.25f);

    EXPECT_EQ(phase_command[0].duty_cycle, 0.625f);
    EXPECT_EQ(phase_command[0].enable, true);

    EXPECT_EQ(phase_command[1].duty_cycle, 0.0f);
    EXPECT_EQ(phase_command[1].enable, true);

    EXPECT_EQ(phase_command[2].duty_cycle, 0.0f);
    EXPECT_EQ(phase_command[2].enable, false);

    six_step.determine_inverter_duty_cycles(phase_command, commutation_steps[1], 1.0f);

    EXPECT_EQ(phase_command[0].duty_cycle, 1.0f);
    EXPECT_EQ(phase_command[0].enable, true);

    EXPECT_EQ(phase_command[1].duty_cycle, 0.0f);
    EXPECT_EQ(phase_command[1].enable, false);

    EXPECT_EQ(phase_command[2].duty_cycle, 0.0f);
    EXPECT_EQ(phase_command[2].enable, true);

    six_step.determine_inverter_duty_cycles(phase_command, commutation_steps[2], 0.5f);

    EXPECT_EQ(phase_command[0].duty_cycle, 0.0f);
    EXPECT_EQ(phase_command[0].enable, false);

    EXPECT_EQ(phase_command[1].duty_cycle, 0.75f);
    EXPECT_EQ(phase_command[1].enable, true);

    EXPECT_EQ(phase_command[2].duty_cycle, 0.0f);
    EXPECT_EQ(phase_command[2].enable, true);
}
