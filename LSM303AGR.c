/*
 * LSM303DLHC.c
 *
 *  Created on: Feb 3, 2025
 *      Author: Govind Bhandari
 */

#include "LSM303AGR.h"
#include "main.h"

char device_id,slave_id;
uint8_t accel_data[6],temp_buffer[2],i;
int16_t accel_x,accel_y,accel_z,temp_data;
float X,Y,Z;

void i2c1_find_my_device()
{
	for(i=0x00; i<=0x7f; i++)
	{
		if(HAL_I2C_IsDeviceReady(LSM303AGR,(uint8_t)(i<<1),1,1000) == HAL_OK)
		{
		device_id = i;
		break;
		}

//		else
//		{
//			device_id = 0;
//		}
	}
}

void LSM303AGR_write_Register(uint8_t reg,uint8_t data)
{
	uint8_t write_buffer[2] = {reg,data};

	HAL_I2C_Master_Transmit(LSM303AGR,LSM303AGR_Dev_addr,write_buffer,2,100);
}

uint8_t LSM303AGR_read_Register(uint8_t reg)
{
	uint8_t data;
	HAL_I2C_Master_Transmit(LSM303AGR,LSM303AGR_Dev_addr,&reg,sizeof(reg),100);
	HAL_I2C_Master_Receive(LSM303AGR,LSM303AGR_Dev_addr,&data,sizeof(data),100);

	return data;
}

void LSM303AGR_Low_power_mode()
{
	LSM303AGR_write_Register(CTRL_REG1_A,0x08);
	LSM303AGR_write_Register(CTRL_REG4_A,0x00);
}

void LSM303AGR_Normal_mode()
{
	LSM303AGR_write_Register(CTRL_REG1_A,0x00);
	LSM303AGR_write_Register(CTRL_REG4_A,0x00);
}

void LSM303AGR_High_resolution_mode()
{
	LSM303AGR_write_Register(CTRL_REG1_A,0x00);
	LSM303AGR_write_Register(CTRL_REG4_A,0x08);
}

void LSM303AGR_init()
{
	LSM303AGR_write_Register(TEMP_CFG_REG_A,0xC0);
	LSM303AGR_write_Register(CTRL_REG1_A,0x57);
	LSM303AGR_write_Register(CTRL_REG4_A,0x08);
	HAL_Delay(10);
}

int16_t LSM303AGR_read_temperature()
{
	uint8_t temp_addr = OUT_TEMP_L_A;

	LSM303AGR_write_Register(TEMP_CFG_REG_A,0xC0);

	HAL_I2C_Master_Transmit(LSM303AGR,LSM303AGR_Dev_addr,&temp_addr,sizeof(temp_addr),100);
	HAL_I2C_Master_Receive(LSM303AGR,LSM303AGR_Dev_addr,temp_buffer,2,100);

	temp_data = ((int16_t)temp_buffer[1] << 8) | temp_buffer[0];

	return temp_data;
}

void LSM303AGR_read_accelerometer()
{
	uint8_t accel_addr = OUT_X_L_A;

	HAL_I2C_Master_Transmit(LSM303AGR,LSM303AGR_Dev_addr,&accel_addr,sizeof(accel_addr),100);
	HAL_I2C_Master_Receive(LSM303AGR,LSM303AGR_Dev_addr,accel_data,6,100);

	accel_x = ((int16_t)(accel_data[1] << 8) | accel_data[0]);
	accel_y = ((int16_t)(accel_data[3] << 8) | accel_data[2]);
	accel_z = ((int16_t)(accel_data[5] << 8) | accel_data[4]);

	X = (float)accel_x / 16384.0;
	Y = (float)accel_y / 16384.0;
	Z = (float)accel_z / 16384.0;
}
