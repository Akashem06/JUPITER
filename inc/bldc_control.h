#ifndef BLDC_CONTROL_H
#define BLDC_CONTROL_H

#include <stdbool.h>
#include <stdint.h>

void bldc_6step_init(void);

void run_bldc_6step(void);

void bldc_6step_commutation(void);
