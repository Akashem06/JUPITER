#ifndef MOCK_CLOCK_HPP
#define MOCK_CLOCK_HPP

#include "gmock/gmock.h"
#include "clock.hpp"

namespace HAL {

class MOCK_JupiterClock : public JupiterClock {
   public:
    MOCK_METHOD(uint32_t, get_time_us, (), (override));
};

}

#endif