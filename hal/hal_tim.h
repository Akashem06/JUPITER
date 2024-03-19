#ifndef HAL_TIME_H
#define HAL_TIME_H

#include <stdint.h>

typedef struct {
    uint32_t current_time;
    uint32_t pwm_duty_cycle;
    uint32_t prescaler;
    uint32_t period;
    uint32_t (*get_time_s)(void);
    void (*set_duty_cycle)(uint8_t duty_cycle);
} Timer;

uint32_t get_delta_time_s(uint32_t time1, uint32_t time2){return time1 - time2;}

void timer_init(Timer *timer);

#endif
