#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <stdint.h>

namespace HAL {

class JupiterClock {
    public:
    JupiterClock() = default;
    virtual ~JupiterClock() {}

    /**
     * @brief Get the current time in microseconds
     * @return The current time in microseconds
     */
    virtual uint32_t get_time_us() = 0;

    /**
     * @brief Get the current time in seconds
     * @return The current time in seconds
     */
    float get_time_s() {
        return static_cast<float>(get_time_us()) / microseconds_per_second;
    }

    /**
     * @brief Get the time difference between two times in microseconds
     * @param t1 The first time (us)
     * @param t2 The second time (us)
     * @return The time difference in microseconds
     */
    static uint32_t get_dt_us(uint32_t time_1, uint32_t time_2) {
        return time_1 - time_2;
    }

    /**
     * @brief Get the time difference between two times in seconds
     * @param t1 The first time (us)
     * @param t2 The second time (us)
     * @return The time difference in seconds
     */
    static float get_dt_s(uint32_t time_1, uint32_t time_2) {
        return static_cast<float>(get_dt_us(time_1, time_2)) / microseconds_per_second;
    }

    /**
     * @brief Get the time difference between two times in x units
     * @param t1 The first time
     * @param t2 The second time
     * @return The time difference in x units
     */
    static float get_dt(uint32_t time_1, uint32_t time_2) {
        return time_1 - time_2;
    }


    /**
     * @brief Number of microseconds per second
     */
    static constexpr float microseconds_per_second = 1000000.0f;
};

}

#endif