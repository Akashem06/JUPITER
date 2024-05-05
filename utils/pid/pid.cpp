#include "pid.hpp"

template <typename T>
void PIDController<T>::reset() {
    integral = 0;
    prev_error = 0;
    prev_measurement = 0;
    last_time = clock.get_time_s();
};

template <typename T>
T PIDController<T>::calculate(double set_point, double measurement) {
    T error = set_point - measurement;
    const uint32_t current_time = clock.get_time_s();
    float d_time = clock.get_dt(current_time, last_time);

    // Trapezoid rule for more accurate integral
    integral = integral + (0.5 * d_time) * (error + prev_error);
    if (math::float_equals(integral_windup, 0) == false) {
        math::clamp(integral, -integral_windup, integral_windup);
    }

    // Prevent divide by 0
    if (math::float_equals(d_time, 0) == false) {
        math::clamp(ema_strength, 0.0f, 1.0f);
        // EMA Filter
        // Discrete time, Low-pass, infinite impulse response (IIR)
        derivative = ema_strength * ((error - prev_error) / d_time) + (1 - ema_strength) * derivative;
    }

    // Low pass filter?

    T output = error * kp + integral * ki + derivative * kd;
    prev_error = error;
    last_time = current_time;

    math::clamp(output, min_output, max_output);

    return output;
}

template <typename T>
float PIDController<T>::get_kp() const {
    return kp;
}

template <typename T>
float PIDController<T>::get_ki() const {
    return ki;
}

template <typename T>
float PIDController<T>::get_kd() const {
    return kd;
}

template <typename T>
void PIDController<T>::set_kp(float kp) {
    this->kp = kp;
}

template <typename T>
void PIDController<T>::set_ki(float ki) {
    this->ki = ki;
}

template <typename T>
void PIDController<T>::set_kd(float kd) {
    this->kd = kd;
}

template <typename T>
void PIDController<T>::set_max_output(T max_output) {
    this->max_output = max_output;
}

template <typename T>
void PIDController<T>::set_min_output(T min_output) {
    this->min_output = min_output;
}

template <typename T>
void PIDController<T>::set_integral_windup(float integral_windup) {
    this->integral_windup = integral_windup;
}

template class PIDController<float>;
template class PIDController<int>;
