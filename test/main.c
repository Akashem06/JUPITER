#include "bldc_control.h"
#include "config.h"
#include "hal_gpio.h"
#include "hal_tim.h"

PhaseConfig_t jupiter_test_config;

int main(void) {
  jupiter_test_setup(&jupiter_test_config);
  return 0;
}
