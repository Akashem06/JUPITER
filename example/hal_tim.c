// User-Defined Example Code

#include "hal_tim.h"

//** EXAMPLE DECLARATIONS OF TIMERS** //
typedef struct {
    uint32_t current_time;
    uint32_t prescaler;
    uint32_t period;
    uint8_t pwm_duty_cycle;
} TimerExample_t;

TimerExample_t timer_example = {
    .current_time = 0,
    .prescaler = 1000000, // Typically people go for 1 Mhz (1 us)
    .period = 0xffffffff,
    .pwm_duty_cycle = 100
};

static uint32_t get_time_s(Timer *timer) {
    return timer->current_time;
}

static void set_duty_cycle(Timer *timer, uint8_t duty_cycle) {
    if (duty_cycle > 100 || duty_cycle < 0) {
        return;
    }
    timer->pwm_duty_cycle = duty_cycle;
}

void timer_init(Timer *timer) {
    timer->get_time_s = get_time_s_instance;
    timer->set_duty_cycle = set_duty_cycle_instance;
}
