#include "bldc_control.h"
#include "config.h"
#include "hal_gpio.h"
#include "hal_tim.h"
#include "unity.h"

PhaseConfig_t jupiter_test_config;

void setUp(void) { jupiter_test_setup(&jupiter_test_config); }

void tearDown(void) {}

void test_case_1(void) {
  bldc_6step_init(30, &jupiter_test_config);

  int a = 1;
  TEST_ASSERT_EQUAL_INT(1, a);  // Passes
}

void test_case_2(void) {
  bldc_6step_init(30, &jupiter_test_config);

  int a = 1;
  TEST_ASSERT_EQUAL_INT(2, a);  // Fails
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_case_1);
  RUN_TEST(test_case_2);

  UNITY_END();

  return 0;
}
