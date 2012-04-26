#include "pid.h"

pid headingPID;  

void setup()
{
	serialWiFlySetup();
	serialMonitorSetup();  
	i2cSetup();
	initializePID(&headingPID, 0.0, 2.0, 0.0, 0.5);
	// try something like 0.5, 1.0, 0.03
}

void loop()
{
	serialMonitor();
	control();
}
