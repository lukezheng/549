  

void setup()
{
  serialWiFlySetup();
  serialMonitorSetup();  
  i2cSetup();
}

void loop()
{
  serialMonitor();  
}
