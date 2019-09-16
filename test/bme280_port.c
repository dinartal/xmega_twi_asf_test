/*
 * port.c
 *
 * Created: 05.06.2018 15:02:36
 *  Author: Динар
 */ 

#include "bme280_port.h"
#include <asf.h>
#include "timer_delay.h"

static struct bme280_dev dev;
static double temperature;
static double humidity;
static double pressure;
static uint8_t BMETValid = 0;

void user_delay_ms(uint32_t period)
{
    /*
     * Return control or wait,
     * for a period amount of milliseconds
     */
	timer_delay(6000);
}

int8_t user_spi_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

    /*
     * The parameter dev_id can be used as a variable to select which Chip Select pin has
     * to be set low to activate the relevant device on the SPI bus
     */

    /*
     * Data on the bus should be like
     * |----------------+---------------------+-------------|
     * | MOSI           | MISO                | Chip Select |
     * |----------------+---------------------|-------------|
     * | (don't care)   | (don't care)        | HIGH        |
     * | (reg_addr)     | (don't care)        | LOW         |
     * | (don't care)   | (reg_data[0])       | LOW         |
     * | (....)         | (....)              | LOW         |
     * | (don't care)   | (reg_data[len - 1]) | LOW         |
     * | (don't care)   | (don't care)        | HIGH        |
     * |----------------+---------------------|-------------|
     */

    return rslt;
}

int8_t user_spi_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

    /*
     * The parameter dev_id can be used as a variable to select which Chip Select pin has
     * to be set low to activate the relevant device on the SPI bus
     */

    /*
     * Data on the bus should be like
     * |---------------------+--------------+-------------|
     * | MOSI                | MISO         | Chip Select |
     * |---------------------+--------------|-------------|
     * | (don't care)        | (don't care) | HIGH        |
     * | (reg_addr)          | (don't care) | LOW         |
     * | (reg_data[0])       | (don't care) | LOW         |
     * | (....)              | (....)       | LOW         |
     * | (reg_data[len - 1]) | (don't care) | LOW         |
     * | (don't care)        | (don't care) | HIGH        |
     * |---------------------+--------------|-------------|
     */

    return rslt;
}

int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
	
	/*
     * The parameter dev_id can be used as a variable to store the I2C address of the device
     */

    /*
     * Data on the bus should be like
     * |------------+---------------------|
     * | I2C action | Data                |
     * |------------+---------------------|
     * | Start      | -                   |
     * | Write      | (reg_addr)          |
     * | Stop       | -                   |
     * | Start      | -                   |
     * | Read       | (reg_data[0])       |
     * | Read       | (....)              |
     * | Read       | (reg_data[len - 1]) |
     * | Stop       | -                   |
     * |------------+---------------------|
     */
	
	volatile int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
	
	twi_package_t packet_read =
	{
		.addr         = {reg_addr},			// TWI slave memory address data
		.addr_length  = sizeof (uint8_t),   // TWI slave memory address data size
		.chip         = dev_id,				// TWI slave bus address
		.buffer       = reg_data,			// transfer data destination buffer
		.length       = len,                   // transfer data size (bytes)
	};
		
	// Perform a multi-byte read access then check the result.
	if(twi_master_read(&TWIC, &packet_read) != TWI_SUCCESS)
	{
	//Check read content
		rslt = -1;
	}
	
	return rslt;
}

int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
	
	/*
     * The parameter dev_id can be used as a variable to store the I2C address of the device
     */

    /*
     * Data on the bus should be like
     * |------------+---------------------|
     * | I2C action | Data                |
     * |------------+---------------------|
     * | Start      | -                   |
     * | Write      | (reg_addr)          |
     * | Write      | (reg_data[0])       |
     * | Write      | (....)              |
     * | Write      | (reg_data[len - 1]) |
     * | Stop       | -                   |
     * |------------+---------------------|
     */
	
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
			
	twi_package_t packet_write =
	{
		.addr         = {reg_addr},      // TWI slave memory address data
		.addr_length  = sizeof (uint8_t),    // TWI slave memory address data size
		.chip         = dev_id,      // TWI slave bus address
		.buffer       = (void *)reg_data, // transfer data source buffer
		.length       = len  // transfer data size (bytes)
	};
			
	while (twi_master_write(&TWIC, &packet_write) != TWI_SUCCESS);

    return rslt;
}

int8_t _bme280_init(void)
{
	twi_master_options_t opt = {
		.speed = TWI_SPEED,
		.speed_reg = TWI_BAUD(F_CPU, TWI_SPEED),
		.chip  = BME280_I2C_ADDR_PRIM
	};
	twi_master_setup(&TWIC, &opt);
	//STATUS_OK
	int8_t rslt = BME280_OK;

	dev.dev_id = BME280_I2C_ADDR_PRIM;
	dev.intf = BME280_I2C_INTF;
	dev.read = user_i2c_read;
	dev.write = user_i2c_write;
	dev.delay_ms = user_delay_ms;

	rslt = bme280_init(&dev);
	
	//
	//Stream sensor data in normal mode
	//
	
	uint8_t settings_sel;

	/* Recommended mode of operation: Indoor navigation */
	dev.settings.osr_h = BME280_OVERSAMPLING_1X;
	dev.settings.osr_p = BME280_OVERSAMPLING_16X;
	dev.settings.osr_t = BME280_OVERSAMPLING_2X;
	dev.settings.filter = BME280_FILTER_COEFF_16;
	dev.settings.standby_time = BME280_STANDBY_TIME_125_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	rslt = bme280_set_sensor_settings(settings_sel, &dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, &dev);
	
	bme280_process();
	
	return rslt;		
}

int8_t _bme280_read_all_d(double *t, double *h, double *p)
{
	struct bme280_data data;
	int8_t rslt = bme280_get_sensor_data(BME280_ALL, &data, &dev);
	
	/*
	In case if "BME280_FLOAT_ENABLE" is not enabled, then it is
	- int32_t for temperature with the units 100 * °C
	- uint32_t for humidity with the units 1024 * % relative humidity
	- uint32_t for pressure
     If macro "BME280_64BIT_ENABLE" is enabled, which it is by default, the unit is 100 * Pascal
     If this macro is disabled, Then the unit is in Pascal
	*/
	
	#ifndef BME280_FLOAT_ENABLE
	*t = data.temperature/100;
	*h = data.humidity/1024;
		#ifdef BME280_64BIT_ENABLE
		*p = data.pressure/100;
		#else
		*p = data.pressure;
		#endif
	#else
	*t = data.temperature;
	*h = data.humidity;
	*p = data.pressure;
	#endif	
	
	return rslt;
}

int8_t _bme280_read_all_i(int32_t *t, uint32_t *h, uint32_t *p)
{
	struct bme280_data data;
	int8_t rslt = bme280_get_sensor_data(BME280_ALL, &data, &dev);
	
	/*
	In case if "BME280_FLOAT_ENABLE" is not enabled, then it is
	- int32_t for temperature with the units 100 * °C
	- uint32_t for humidity with the units 1024 * % relative humidity
	- uint32_t for pressure
     If macro "BME280_64BIT_ENABLE" is enabled, which it is by default, the unit is 100 * Pascal
     If this macro is disabled, Then the unit is in Pascal
	*/
	
	#ifndef BME280_FLOAT_ENABLE
	*t = data.temperature/100;
	*h = data.humidity/1024;
		#ifdef BME280_64BIT_ENABLE
		*p = data.pressure/100;
		#else
		*p = data.pressure;
		#endif
	#else
	*t = data.temperature;
	*h = data.humidity;
	*p = data.pressure;
	#endif	
	
	return rslt;
}

int8_t _bme280_read_100t(int32_t *t)
{
	struct bme280_data data;
	int8_t rslt = bme280_get_sensor_data(BME280_TEMP, &data, &dev);
	
	#ifndef BME280_FLOAT_ENABLE
	*t = data.temperature;
	#else
	*t = data.temperature * 100;
	#endif
	
	return rslt;
}

void bme280_process(void)
{
	//проверка на валидность
	static uint8_t tbme_good_counter = 0;	
	if (_bme280_read_all_d(&temperature, &humidity, &pressure) != BME280_OK)
	{
		temperature=-300;
		humidity=-300;
		pressure=-300;

		BMETValid=0;
		tbme_good_counter=0;		
	}
	else
	{
		//convert to mm rt stolba
		pressure*=0.00750062;
		
		if (++tbme_good_counter==3)
		{
			tbme_good_counter=2;
			BMETValid=1;
		}
	}
}

double bme280_get_t_d(void)
{
	//return 40;
	return temperature;
}

double bme280_get_h_d(void)
{
	return humidity;
}

double bme280_get_p_d(void)
{
	return pressure;
}

void _bme280_deinit(void)
{
	twi_master_disable(&TWIC);
	sysclk_disable_peripheral_clock(&TWIC);
}

uint8_t isBMETValid(void)
{
	return BMETValid;
}