#include "math.hpp"

#include <cmath>

namespace math {

bool float_equals(const float a, const float b) { return fabs(a - b) < FLOAT_ERROR_BUFFER; }

}  // namespace math