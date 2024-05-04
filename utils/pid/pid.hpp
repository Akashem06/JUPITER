#ifndef PID_CONTROL_HPP
#define PID_CONTROL_HPP

#include <iostream>
#include "status.hpp"
#include "clock.hpp"
#include "math.hpp"

template <typename T>
class PIDController {
    private:
        float kp, ki, kd;
        float integral_windup;
        float integral, derivative;
        hal::JupiterClock &clock;
        T prev_error, prev_measurement;
        T max_output, min_output;
        uint32_t last_time;
    public:
    
        PIDController(double kp, double ki, double kd, T min_output, T max_output, float integral_windup, hal::JupiterClock &clock)
        :   kp(kp), ki(ki), kd(kd),
            integral_windup(integral_windup),
            integral(0), derivative(0),
            clock(clock),
            prev_error(0), prev_measurement(0),
            max_output(max_output), min_output(min_output),
            last_time(0) {}

        /**
        * @brief Resets the PID controllers integral/error/clock
         */
        void reset();

        /**
        * @brief Calculates the output of PID Controller
        * @param set_point Benchmark measurement (ie: Cruise control target speed)
        * @param measurement Actual measurement (ie: Vehicles velocity)
        * @return Updated output of PID Controller
         */
        T calculate(double set_point, double measurement);

        /**
        * @brief Returns proportional gain in PID controller
         */
        float get_kp() const;

        /**
        * @brief Returns integral gain in PID controller
         */
        float get_ki() const;

        /**
        * @brief Returns derivative gain in PID controller
         */
        float get_kd() const;

        /**
         * @brief Sets the proportional gain value
         * @param kp The proportional gain value
         */
        void set_kp(float kp);

        /**
         * @brief Set the integral gain value
         * @param ki The integral gain value
         */
        void set_ki(float ki);

        /**
         * @brief Set the derivative gain value
         * @param kd The derivative gain value
         */
        void set_kd(float kd);

        /**
         * @brief Set the max output value
         * @param max_output the max output value
         */
        void set_max_output(T max_output);

        /**
         * @brief Set the min output value
         * @param min_output the min output value
         */
        void set_min_output(T min_output);

        /**
         * @brief Set the integral windup value
         * @param integral_windup The integral windup value as an absolute value
         */
        void set_integral_windup(float integral_windup);
};

#endif