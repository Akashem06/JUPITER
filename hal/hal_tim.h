#ifndef HAL_TIME_H
#define HAL_TIME_H

uint32_t get_time_s(void);

void set_duty_cycle(uint8_t duty_cycle);

uint32_t get_delta_time_s(uint32_t time1, uint32_t time2){return time1 - time2};

#endif
