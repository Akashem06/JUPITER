#ifndef MATH_HPP
#define MATH_HPP

namespace math {

constexpr float FLOAT_ERROR_BUFFER = 0.000001f;

/**
 * @brief Determine whether two floats are equal
 * @param a First float
 * @param b Second float
 * @return True if floats are equal, False if not
 */
bool float_equals(float a, float b);

/**
 * @brief Clamp the given value between the given min and max values
 * @param value The value to clamp
 * @param min The minimum value
 * @param max The maximum value
 * @return void
 */
template <typename T>
void clamp(T& value, const T& min, const T& max) {
    if (value < min) {
        value = min;
    } else if (value > max) {
        value = max;
    } else {
    }
}

}

#endif