/*
 * timer_delay.c
 *
 * Created: 01.08.2018 13:31:46
 *  Author: Динар
 */ 

#include "asf.h"
#include "timer_delay.h"

void timer_delay_init(void)
{
	tc_enable(&TCC1);
	tc_set_wgm(&TCC1, TC_WG_NORMAL);
	tc_write_clock_source(&TCC1, TC_CLKSEL_DIV8_gc);
	tc_write_period(&TCC1, 65535);	
}

void timer_delay(uint16_t ticks)
{
	tc_write_count(&TCC1,0);
	while(tc_read_count(&TCC1)<ticks);	
}