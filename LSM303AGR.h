/*
 * LSM303DLHC.h
 *
 *  Created on: Feb 3, 2025
 *      Author: Govind Bhandari
 */

#ifndef INC_LSM303AGR_H_
#define IINC_LSM303AGR_H_

#include "main.h"

#define LSM303AGR_Dev_addr  (0x19 << 1)
extern I2C_HandleTypeDef    hi2c1;
#define LSM303AGR           &hi2c1

//LSM303DLHC Register Mapping
#define STATUS_REG_AUX_A   0x07
#define OUT_TEMP_L_A       0x0C
#define OUT_TEMP_H_A       0x0D
#define WHO_AM_I_A         0x0F
#define TEMP_CFG_REG_A     0x1F
#define CTRL_REG1_A        0x20
#define CTRL_REG2_A        0x21
#define CTRL_REG3_A        0x22
#define CTRL_REG4_A        0x23
#define CTRL_REG5_A        0x24
#define CTRL_REG6_A        0x25
#define DATACAPTURE_A      0x26
#define STATUS_REG_A       0x27
#define OUT_X_L_A          0x28
#define OUT_X_H_A          0x29
#define OUT_Y_L_A          0x2A
#define OUT_Y_H_A          0x2B
#define OUT_Z_L_A          0x2C
#define OUT_Z_H_A          0x2D



void i2c1_find_my_device();
void LSM303AGR_init();
int16_t LSM303AGR_read_temperature();
void LSM303AGR_read_accelerometer();

#endif /*INC_LSM303AGR_H_*/
