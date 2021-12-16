/*
 * main.c
 *
 *  Created on: 15 Ara 2021
 *      Author: Ali
 */

#include <mpu6050.h>
#include <sys/ioctl.h>

/*
 ==========================================================================
 MPU6050 	 BBB PIN NO
 VCC			P9_3
 GND			P9_1
 SCL			P9_19
 SDA			P9_20
 ==========================================================================
 */

MPU6050_ACC_DATA_t mpu6050_accData_t;
MPU6050_GYRO_DATA_t mpu6050_gyroData_t;

int fd;

int main() {
	fd = open(I2C_DEVICE_FILE_PATH,O_RDWR);

    if ( fd < 0) {
        perror("Failed to open I2C device file.\n");
        return -1;
    }

    /*set the I2C slave address  */
    if (ioctl(fd,I2C_SLAVE,MPU6050_SLAVE_ADDRESS) < 0) {
            perror("Failed to set I2C slave address.\n");
            close(fd);
            return -1;
    }

    mpu6050_init();

    while(1) {
    	mpu6050_readAcc();
    	mpu6050_readGyro();

    	printf("accX:  %0.2f accY:  %.02f accZ:  %0.2f\n", mpu6050_accData_t.accX, mpu6050_accData_t.accY, mpu6050_accData_t.accZ);
    	printf("gyroX: %0.2f gyroY: %.02f gyroZ: %0.2f\n", mpu6050_gyroData_t.gyroX, mpu6050_gyroData_t.gyroY, mpu6050_gyroData_t.gyroZ);
    	printf("Temp %0.2f\n\n", mpu6050_readTemp() );
    	usleep(500* 1000);
    }
	return 0;
}
