#ifndef HAL_TIME_H
#define HAL_TIME_H

#include <stdint.h>

typedef struct {
    uint32_t current_time;
    uint32_t pwm_duty_cycle;
    uint32_t prescaler;
    uint32_t period;
} Timer;

uint32_t get_time_s(Timer *timer);
void set_duty_cycle(Timer *timer, uint8_t duty_cycle);

void timer_init(Timer *timer);

#endif
