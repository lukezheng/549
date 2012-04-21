#include "pid.h"

pid headingPID;  

void setup()
{
  serialWiFlySetup();
  serialMonitorSetup();  
  i2cSetup();
  initializePID(&headingPID, 0.5, 4.0, 0.0, 1.0);
}

void loop()
{
  serialMonitor();  
}
