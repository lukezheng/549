
#include <Wire.h>
#include "constants.h"

void i2cSetup()
{
  Wire.begin();  
}

void i2cWrite(int address, int data)
{
  Wire.beginTransmission(address);
  Wire.write(data);
  Wire.endTransmission();  
}
