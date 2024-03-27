#include "bldc_control.h"
#include "bldc_control_prv.h"
#include "config.h"
#include "hal_gpio.h"
#include "hal_tim.h"
#include "unity.h"
#include <string.h>

PhaseConfig_t jupiter_test_config;

void setUp(void) { jupiter_test_setup(&jupiter_test_config); }

void tearDown(void) {}

void init_arrays(uint8_t zeroCrossing_arr[3], uint8_t reference_arr[3]) {
    memset(zeroCrossing_arr, 0, sizeof(uint8_t) * 3);
    memset(reference_arr, 0, sizeof(uint8_t) * 3);
}

void set_zcross_pins(uint8_t zcross_a, uint8_t zcross_b, uint8_t zcross_c) {
  jupiter_test_config.phase_A.zcross.gpio_state = zcross_a;
  jupiter_test_config.phase_B.zcross.gpio_state = zcross_b;
  jupiter_test_config.phase_C.zcross.gpio_state = zcross_c;
}

void test_zero_crossing_read(void) {
  bldc_6step_init(30, &jupiter_test_config);

  uint8_t zeroCrossing_arr[3];
  uint8_t reference_arr[3];
  init_arrays(zeroCrossing_arr, reference_arr);

  prv_zero_crossing(zeroCrossing_arr);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(reference_arr, zeroCrossing_arr, 3);

  set_zcross_pins(1, 0, 0);
  reference_arr[0] = 1;
  prv_zero_crossing(zeroCrossing_arr);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(reference_arr, zeroCrossing_arr, 3);

  set_zcross_pins(0, 1, 1);
  reference_arr[0] = 0;
  reference_arr[1] = 1;
  reference_arr[2] = 1;
  prv_zero_crossing(zeroCrossing_arr);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(reference_arr, zeroCrossing_arr, 3);
}

void test_case_1(void) {
  bldc_6step_init(30, &jupiter_test_config);

  uint8_t zeroCrossing_arr[3];
  uint8_t reference_arr[3];
  init_arrays(zeroCrossing_arr, reference_arr);
  reference_arr[0] = 1;

  set_zcross_pins(1, 0 ,0);

  prv_zero_crossing(zeroCrossing_arr);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(reference_arr, zeroCrossing_arr, 3);

  prv_get_commutation_step
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_zero_crossing_read);
  RUN_TEST(test_case_1);

  UNITY_END();

  return 0;
}
