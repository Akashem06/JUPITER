//** EXAMPLE DECLARATIONS OF TIMERS** //

#include "hal_tim.h"

uint32_t get_time_s(Timer *timer) {
  return timer->current_time;
}

void set_duty_cycle(Timer *timer, uint8_t duty_cycle) {
  if (duty_cycle > 100) {
    return;
  }
  timer->pwm_duty_cycle = duty_cycle;
}

void timer_init(Timer *timer) {}

//** EXAMPLE INITILIZATION OF TIMERS** //

Timer timer_example_phaseA = { .current_time = 0,
                               .prescaler = 1000000,  // Typically people go for 1 Mhz (1 us)
                               .period = 0xffffffff,
                               .pwm_duty_cycle = 33 };

Timer timer_example_phaseB = { .current_time = 0,
                               .prescaler = 1000000,  // Typically people go for 1 Mhz (1 us)
                               .period = 0xffffffff,
                               .pwm_duty_cycle = 33 };

Timer timer_example_phaseC = { .current_time = 0,
                               .prescaler = 1000000,  // Typically people go for 1 Mhz (1 us)
                               .period = 0xffffffff,
                               .pwm_duty_cycle = 33 };