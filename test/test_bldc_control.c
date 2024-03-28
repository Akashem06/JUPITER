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

void init_array(uint8_t array[3]) {
    memset(array, 0, sizeof(uint8_t) * 3);
}

void set_zcross_pins(uint8_t zcross_a, uint8_t zcross_b, uint8_t zcross_c) {
  jupiter_test_config.phase_A.zcross.gpio_state = zcross_a;
  jupiter_test_config.phase_B.zcross.gpio_state = zcross_b;
  jupiter_test_config.phase_C.zcross.gpio_state = zcross_c;
}

void set_zcross_arr(uint8_t zeroCrossings[], uint8_t zcross_a, uint8_t zcross_b, uint8_t zcross_c) {
  zeroCrossings[0] = zcross_a;
  zeroCrossings[1] = zcross_b;
  zeroCrossings[2] = zcross_c;
}

void test_zero_crossing_read(void) {
  bldc_6step_init(30, &jupiter_test_config);

  uint8_t zeroCrossing_arr[3];
  uint8_t reference_arr[3];
  init_array(zeroCrossing_arr);
  init_array(reference_arr);

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

void test_get_commutation_step(void) {
  bldc_6step_init(30, &jupiter_test_config);

  uint8_t zeroCrossing_arr[3];
  uint8_t comm_step;
  init_array(zeroCrossing_arr);

  set_zcross_arr(zeroCrossing_arr, 0, 1, 1);
  comm_step = prv_get_commutation_step(zeroCrossing_arr);
  TEST_ASSERT_EQUAL_UINT8(3, comm_step);

  set_zcross_arr(zeroCrossing_arr, 1, 1, 1);
  comm_step = prv_get_commutation_step(zeroCrossing_arr);
  TEST_ASSERT_EQUAL_UINT8(0xff, comm_step);

  set_zcross_arr(zeroCrossing_arr, 0, 0, 0);
  comm_step = prv_get_commutation_step(zeroCrossing_arr);
  TEST_ASSERT_EQUAL_UINT8(0xff, comm_step);

  set_zcross_arr(zeroCrossing_arr, 1, 0, 0);
  comm_step = prv_get_commutation_step(zeroCrossing_arr);
  TEST_ASSERT_EQUAL_UINT8(0, comm_step);
}

void test_case_1(void) {
  bldc_6step_init(30, &jupiter_test_config);

  uint8_t zeroCrossing_arr[3];
  uint8_t reference_arr[3];
  init_array(zeroCrossing_arr);
  init_array(reference_arr);
  reference_arr[0] = 1;

  set_zcross_pins(1, 0 ,0);

  prv_zero_crossing(zeroCrossing_arr);
  TEST_ASSERT_EQUAL_UINT8_ARRAY(reference_arr, zeroCrossing_arr, 3);

}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_zero_crossing_read);
  RUN_TEST(test_get_commutation_step);
  RUN_TEST(test_case_1);

  UNITY_END();

  return 0;
}
