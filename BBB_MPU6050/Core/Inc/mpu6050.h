/*
 * mpu6050.h
 *
 *  Created on: 15 Ara 2021
 *      Author: Ali Celik
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdint.h>

#define SLEEP_MODE_DEACTIVATED	0x00
#define SLEEP_MODE_ACTIVATED	0x40
#define ACC_ST_DEACTIVATED		0x00
#define GYRO_ST_DEACTIVATED		0x00

#define MPU6050_PWR_MGMT_1		0x6B
#define MPU6050_PWR_MGMT_2		0x6C
#define MPU6050_GYRO_CONFIG		0x1B
#define MPU6050_ACC_CONFIG		0x1C

/* Accelerometer */
#define MPU6050_ACC_XOUT_H		0x3B
#define MPU6050_ACC_XOUT_L		0x3C
#define MPU6050_ACC_YOUT_H		0x3D
#define MPU6050_ACC_YOUT_L		0x3E
#define MPU6050_ACC_ZOUT_H		0x3F
#define MPU6050_ACC_ZOUT_L		0x40

/* Temperature*/
#define MPU6050_TEMP_OUT_H		0x41
#define MPU6050_TEMP_OUT_L		0x42

/* Gyroscope  */
#define MPU6050_GYRO_XOUT_H		0x43
#define MPU6050_GYRO_XOUT_L		0x44
#define MPU6050_GYRO_YOUT_H		0x45
#define MPU6050_GYRO_YOUT_L		0x46
#define MPU6050_GYRO_ZOUT_H		0x47
#define MPU6050_GYRO_ZOUT_L		0x48

/* Gyro and accel full-scale range*/
#define MPU6050_GYRO_FS_SEL_0	131
#define MPU6050_GYRO_FS_SEL_1	65.5
#define MPU6050_GYRO_FS_SEL_2	32.8
#define MPU6050_GYRO_FS_SEL_3	16.4

#define MPU6050_ACC_FS_SEL_0	16384
#define MPU6050_ACC_FS_SEL_1	8192
#define MPU6050_ACC_FS_SEL_2	4096
#define MPU6050_ACC_FS_SEL_3	2048

#define MPU6050_SLAVE_ADDRESS	0x68

#define I2C_DEVICE_FILE_PATH	"/dev/i2c-2"

typedef struct {
	double accX;
	double accY;
	double accZ;
}MPU6050_ACC_DATA_t;

typedef struct {
	double gyroX;
	double gyroY;
	double gyroZ;
}MPU6050_GYRO_DATA_t;

int mpu6050_write(uint8_t address, uint8_t data);
int mpu6050_read(uint8_t address, char *pBuffer, uint8_t len);
int mpu6050_init(void);
void mpu6050_readAcc(void);
void mpu6050_readGyro(void);
double mpu6050_readTemp(void);

#endif /* INC_MPU6050_H_ */
