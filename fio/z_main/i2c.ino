#include <Wire.h>
#include "i2c.h"

void i2cSetup()
{
  Wire.begin();

  int magno_register = 0x02;
  int magno_mode = 0x00;

  Wire.beginTransmission(MAGNETOMETER_ADDR);
  // select mode register
  Wire.write(magno_register);
  // continuous measure
  Wire.write(magno_mode);
  Wire.endTransmission();    
}

void i2cWrite(int address, int data)
{
  Wire.beginTransmission(address);
  Wire.write(data);
  Wire.endTransmission();  
}

// returns 0 on success, 1 on error
int i2cRead(int address, int bytes, byte* start)
{
  int i;
  
  Wire.requestFrom(address, bytes);

  if(bytes <= Wire.available())
  {
    for (i=0; i<bytes; i++)
    {
      *start = Wire.read();
      start++;  
    }
    
    return 0;
  }  
  
  return 1;
}
