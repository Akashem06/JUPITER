#include "bldc_control.h"
#include "config.h"
#include "hal_gpio.h"
#include "hal_tim.h"
#include "unity.h"

PhaseConfig_t jupiter_test_config;

void setUp(void) {}    /* Is run before every test, put unit init calls here. */
void tearDown(void) {} /* Is run after every test, put unit clean-up calls here. */

int main(void) {
  jupiter_test_setup(&jupiter_test_config);

  bldc_6step_init(30, &jupiter_test_config);
  printf("Hey test is running\n");
  int a = 1;
  TEST_ASSERT( a == 1 ); //this one will pass
  // TEST_ASSERT( a == 2 ); //this one will fail
  while (true) {
  }

  return 0;
}
