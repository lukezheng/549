#include <SoftwareSerial.h>
#include "constants.h"

SoftwareSerial monitorSerial(MONITOR_RX_PORT, MONITOR_TX_PORT);

void serialMonitorSetup()
{
  monitorSerial.begin(MONITOR_BDRATE);  
}

void serialWiFlySetup()
{
  Serial.begin(WIFLY_BDRATE); 
}

void serialMonitor()
{
  if (monitorSerial.available())
    Serial.write(monitorSerial.read());
  if (Serial.available())
    monitorSerial.write(Serial.read());  
}
