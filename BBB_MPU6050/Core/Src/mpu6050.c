/*
 ============================================================================
 Name        : mpu6050.c
 Author      : Ali Celik
 Version     :
 Copyright   : Your copyright notice
 Description : MPU6050
 ============================================================================
*/

#include <mpu6050.h>

MPU6050_ACC_DATA_t mpu6050_accData_t;
MPU6050_GYRO_DATA_t mpu6050_gyroData_t;

int fd;

int mpu6050_write(uint8_t address, uint8_t data) {
	int ret;
	char buf[2];
	buf[0] = address;
	buf[1] = data;
	ret = write(fd,buf,2);
	if( ret <= 0) {
		perror("Write failed/n");
		return -1;
	}

	return 0;
}

int mpu6050_read(uint8_t address, char *pBuffer, uint8_t len) {
	int ret;
	char buf[1];
	buf[0]= address;
	ret = write(fd,buf,1);
	if (ret <= 0) {
	  perror("Write address failed\n");
	  return -1;
	}

	ret = read(fd,pBuffer,len);
	if(ret <= 0) {
	  perror("Read failed\n");
	  return -1;
	}

	return 0;
}

int mpu6050_init(void) {
    mpu6050_write(MPU6050_PWR_MGMT_1, SLEEP_MODE_DEACTIVATED);
    usleep(500);
    mpu6050_write(MPU6050_ACC_CONFIG, ACC_ST_DEACTIVATED);
    usleep(500);
    mpu6050_write(MPU6050_GYRO_CONFIG, GYRO_ST_DEACTIVATED);
    usleep(500);

    return 0;
}

void mpu6050_readAcc(void) {
    //each axis value is of 2byte
    char accBuffer[6];
    short X,Y,Z;


    //start reading from the base address of accelerometer values MPU6050_GYRO_XOUT_H
    mpu6050_read(MPU6050_ACC_XOUT_H,accBuffer,6);

    /*read raw value*/
    X = (int) ( (accBuffer[0] << 8) |  accBuffer[1] );
    Y = (int) ( (accBuffer[2] << 8) |  accBuffer[3] );
    Z = (int) ( (accBuffer[4] << 8) |  accBuffer[5] );

    /* convert to g value*/
    mpu6050_accData_t.accX = (double)X / MPU6050_ACC_FS_SEL_0;
    mpu6050_accData_t.accY = (double)Y / MPU6050_ACC_FS_SEL_0;
    mpu6050_accData_t.accZ = (double)Z / MPU6050_ACC_FS_SEL_0;
}

/* read gyro values of x,y,z in to the buffer "pBuffer" */
void mpu6050_readGyro(void) {
    char gyroBuffer[6];
    short X,Y,Z;
    //start reading from the base address of gyro values  MPU6050_REG_GYRO_X_HIGH
    mpu6050_read(MPU6050_GYRO_XOUT_H,gyroBuffer,6);

    /* read raw data*/
    X =  ( (gyroBuffer[0] << 8) +  gyroBuffer[1] );
    Y =  ( (gyroBuffer[2] << 8) +  gyroBuffer[3] );
    Z =  ( (gyroBuffer[4] << 8) +  gyroBuffer[5] );

    /*convert to g data*/
    mpu6050_gyroData_t.gyroX =  (double) X / MPU6050_GYRO_FS_SEL_0;
    mpu6050_gyroData_t.gyroY =  (double) Y / MPU6050_GYRO_FS_SEL_0;
    mpu6050_gyroData_t.gyroZ =	(double) Z / MPU6050_GYRO_FS_SEL_0;

}

double mpu6050_readTemp(void) {
	char tempBuffer[2];
	short temp;
	double tempC;
	//start reading from the base address of temperature MPU6050_TEMP_OUT_H
	mpu6050_read(MPU6050_TEMP_OUT_H,tempBuffer,2);

	temp = ( (tempBuffer[0] << 8) + tempBuffer[1] );
	//convert to celcius
	tempC = (double)temp / 340 + 36.53;

	return tempC;
}
