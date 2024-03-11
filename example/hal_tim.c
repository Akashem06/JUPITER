// User-Defined Example Code

#include "hal_tim.h"

static uint32_t get_time_s_instance(Timer *timer) {
    timer->current_time++;
    return timer->current_time;
}

static void set_duty_cycle_instance(Timer *timer, uint8_t duty_cycle) {}

void timer_init(Timer *timer) {
    timer->current_time = 0;
    timer->get_time_s = get_time_s_instance;
    timer->set_duty_cycle = set_duty_cycle_instance;
}
