#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mocks/mock_clock.hpp"
#include "pid.hpp"

using namespace ::testing;

TEST(PIDTest, proportional_gain_test) {
    hal::MOCK_JupiterClock mock_clock;
    PIDController<float> pid(1, 0, 0, -10, 10, 0, mock_clock);

    EXPECT_EQ(pid.get_kp(), 1.0);

    // Expect a call to get_time_us() to return 500
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(500));
    EXPECT_EQ(pid.calculate(0, 1.0), -1);

    // Expect a call to get_time_us() to return 123
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(123));
    EXPECT_EQ(pid.calculate(20, 0), 10);  // Verify capping :D

    // Expect a call to get_time_us() to return 5555
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(5555));
    EXPECT_EQ(pid.calculate(0.456, 0.456), 0);
}

TEST(PIDTest, integral_gain_test) {
    hal::MOCK_JupiterClock mock_clock;
    PIDController<float> pid(0, 1, 0, -10, 10, 5, mock_clock);

    EXPECT_EQ(pid.get_ki(), 1.0);

    // Expect a call to get_time_us() to return 1 * microseconds_per_second
    // At time t0, with error = 1.0 and no previous error, the integral should be 0.5
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(1 * hal::MOCK_JupiterClock::microseconds_per_second));
    EXPECT_EQ(pid.calculate(1.0, 0.0), 0.5);

    // Expect a call to get_time_us() to return 2 * microseconds_per_second
    // At time t1, with error = 0.5 and previous error = 1.0, the integral should be 1.25
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(2 * hal::MOCK_JupiterClock::microseconds_per_second));
    EXPECT_EQ(pid.calculate(1.0, 0.5), 1.25);

    // Expect a call to get_time_us() to return 3 * microseconds_per_second
    // At time t2, with error = -0.75 and previous error = 0.5, the integral should be 1.125
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(3 * hal::MOCK_JupiterClock::microseconds_per_second));
    EXPECT_EQ(pid.calculate(1.0, 1.75), 1.125);

    // Expect a call to get_time_us() to return 20 * microseconds_per_second
    // Testing Integral windup capping
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(20 * hal::MOCK_JupiterClock::microseconds_per_second));
    EXPECT_EQ(pid.calculate(1.0, 1.75), -5);  // Assume something is holding us 0.75 above the setpoint

    // Expect a call to get_time_us() to return 3 * microseconds_per_second
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(22 * hal::MOCK_JupiterClock::microseconds_per_second));
    EXPECT_EQ(pid.calculate(1.0, 0.85), -5);

    // Expect a call to get_time_us() to return 3 * microseconds_per_second
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(24 * hal::MOCK_JupiterClock::microseconds_per_second));
    EXPECT_EQ(pid.calculate(1.0, 0.55), -4.4f);
}

TEST(PIDTest, derivative_gain_test) {
    hal::MOCK_JupiterClock mock_clock;
    PIDController<float> pid(0, 0, 1, -10, 10, 0, mock_clock);

    EXPECT_EQ(pid.get_kd(), 1.0);

    // Expect a call to get_time_us() to return 1*basilisk_hal::HAL_CLOCK::kMicrosecondsPerSecond
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(1 * hal::MOCK_JupiterClock::microseconds_per_second));
    EXPECT_EQ(pid.calculate(1.0, 0.0), 1);

    // Expect a call to get_time_us() to return 2*basilisk_hal::HAL_CLOCK::kMicrosecondsPerSecond
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(3 * hal::MOCK_JupiterClock::microseconds_per_second));
    EXPECT_EQ(pid.calculate(1, 0.8), -0.4f);

    // Expect a call to get_time_us() to return 3*basilisk_hal::HAL_CLOCK::kMicrosecondsPerSecond
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(7 * hal::MOCK_JupiterClock::microseconds_per_second));
    EXPECT_EQ(pid.calculate(1, 1.2), -0.1f);

    // Expect a call to get_time_us() to return 4*basilisk_hal::HAL_CLOCK::kMicrosecondsPerSecond
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(9 * hal::MOCK_JupiterClock::microseconds_per_second));
    EXPECT_EQ(pid.calculate(1, 1.1), 0.05f);
}

TEST(PIDTest, MaxOutputTest) {
    hal::MOCK_JupiterClock mock_clock;
    PIDController<float> pid(1, 0, 0, -10, 10, 0, mock_clock);

    // Expect a call to get_time_us() to return 1
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(1));
    EXPECT_EQ(pid.calculate(1000.0, 0.0), 10);
}

TEST(PIDTest, MinOutputTest) {
    hal::MOCK_JupiterClock mock_clock;
    PIDController<float> pid(1, 0, 0, -10, 10, 0, mock_clock);

    // Expect a call to get_time_us() to return 1
    EXPECT_CALL(mock_clock, get_time_us()).WillOnce(Return(1));
    EXPECT_EQ(pid.calculate(-1000.0, 0.0), -10);
}

TEST(PIDTest, initialize_test) {
    hal::MOCK_JupiterClock mock_clock;
    PIDController<float> pid(1, 1.23, 0.96, -10, 10, 0, mock_clock);

    EXPECT_EQ(pid.get_kp(), 1);
    EXPECT_EQ(pid.get_ki(), 1.23f);
    EXPECT_EQ(pid.get_kd(), 0.96f);
}
