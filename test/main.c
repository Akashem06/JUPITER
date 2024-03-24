#include "bldc_control.h"
#include "config.h"
#include "hal_gpio.h"
#include "hal_tim.h"

PhaseConfig_t jupiter_test_config;

int main(void) {
  jupiter_test_setup(&jupiter_test_config);
  
  bldc_6step_init(30, &jupiter_test_config);

  while (true) {
    run_bldc_6step();
  }
  
  return 0;
}
