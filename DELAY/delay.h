#ifndef __DELAY_H
#define	__DELAY_H

#include "stm32l0xx_hal.h"

void delay_us(uint16_t time);
void delay_ms(uint16_t time);
void delay_sec(uint16_t time);

#endif /* __DELAY_H */
