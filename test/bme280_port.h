/*
 * bme280_port.h
 *
 * Created: 05.06.2018 15:02:21
 *  Author: Динар
 */ 


#ifndef BME280_PORT_H_
#define BME280_PORT_H_

#ifndef F_CPU
#define F_CPU 48000000UL
#endif

#define TWI_SPEED 100000

#include <avr/io.h>
#include <twi_master.h>
//#include <util/delay.h>
#include "bme280.h"
//#include "t_settings.h"

void user_delay_ms(uint32_t period);
int8_t user_spi_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t user_spi_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t _bme280_init(void);
int8_t _bme280_read_all_d(double *t, double *h, double *p);
int8_t _bme280_read_all_i(int32_t *t, uint32_t *h, uint32_t *p);
int8_t _bme280_read_100t(int32_t *t);
void bme280_process(void);
double bme280_get_t_d(void);
double bme280_get_h_d(void);
double bme280_get_p_d(void);
void _bme280_deinit(void);
uint8_t isBMETValid(void);

#endif /* BME280_PORT_H_ */