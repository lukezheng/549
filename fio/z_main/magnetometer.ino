#include "magnetometer.h"


void readMagnetometer(int* x, int* y, int* z)
{
	// Tell the HMC5883 to begin reading at register 3, X's MSB register
	i2cWrite(MAGNETOMETER_ADDR, 0x03);
 
	byte array[6];
  
	i2cRead(MAGNETOMETER_ADDR, 6, array);

  
	*x = array[0] << 8;  // X msb
	*x |= array[1];      // X lsb
	*z = array[2] << 8;  // Z msb
	*z |= array[3];      // Z lsb
	*y = array[4] << 8;  // Y msb
	*y |= array[5];      // Y lsb 

	toAngle(*x, *y);  
}

void toAngle(int x, int y)
{
	if (y != 0)
		currentDirection = atan2((y+Y_OFFSET)*Y_SCALE, (x+X_OFFSET)*X_SCALE);
	else if (x < 0)
		currentDirection = PI;
	else
		currentDirection = 0.0;
}
