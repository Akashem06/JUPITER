#include "pwm.h"

#include "bldc_control.h"
#include "hal_tim.h"

void set_phaseA_duty(uint32_t duty_cycle, bool enable) {
    if (enable) {
        set_duty_cycle(duty_cycle);
    } else {
        set_duty_cycle(0);
    }
}
