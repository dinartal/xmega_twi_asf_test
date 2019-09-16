/*
 * test.c
 *
 * Created: 16.09.2019 15:06:31
 * Author : Динар
 */ 

#include <asf.h>
#include "timer_delay.h"
#include "bme280_port.h"
#include "stdio.h"
#include "string.h"

int main(void)
{
	sysclk_init();
	irq_initialize_vectors();
	timer_delay_init();
    _bme280_init();
	udc_start();
    while (1) 
    {
		// 1s delay 
		for (int i=0; i<1000; i++)
		{
			timer_delay(6000);
		}
		
		//print BME280 data
		bme280_process();
		int t = bme280_get_t_d(); //use int to simplify output, %lf not supported by default
		char buf[30];
		sprintf(buf, "Temperature: %d\r\n", t);
		udi_cdc_write_buf(buf, strlen(buf));
    }
}




void user_callback_vbus_action(bool b_vbus_high)
{
	
}

void user_callback_sof_action(void)
{
	
}

void user_callback_suspend_action(void)
{
	
}

void user_callback_resume_action(void)
{
	
}

bool my_callback_cdc_enable(void)
{
	return 1;
}

void my_callback_cdc_disable(void)
{
	
}

void my_callback_rx_notify(uint8_t port)
{

}

void my_callback_tx_empty_notify(uint8_t port)
{

}

void my_callback_config(uint8_t port, usb_cdc_line_coding_t * cfg)
{
	
}

void my_callback_cdc_set_dtr(uint8_t port, bool b_enable)
{
	
}

void my_callback_cdc_set_rts(uint8_t port, bool b_enable)
{
	
}