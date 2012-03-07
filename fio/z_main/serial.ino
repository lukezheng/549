#include <SoftwareSerial.h>
#include "constants.h"

SoftwareSerial monitorSerial(MONITOR_RX_PORT, MONITOR_TX_PORT);
int iIncomingByte = 0;
int i=0;
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
  {  
    iIncomingByte = Serial.read();
    monitorSerial.write(iIncomingByte);
/*
    monitorSerial.print("Motor: ");    
    switch (GET_MOTOR(iIncomingByte))
    {
      case VERTICAL:
        monitorSerial.print("VERT"); 
        break;
      
      case SIDE:
        monitorSerial.print("SIDE");
        break;
    
      case FRONT_LEFT:
        monitorSerial.print("FLFT");
        break;
    
      case FRONT_RIGHT:
        monitorSerial.print("FRGT");
        break;
      
      default:
        monitorSerial.print("ERRO");
        break;  
    } 
    
//    monitorSerial.print(GET_MOTOR(iIncomingByte), DEC);

    monitorSerial.print(" Direction: ");
    if (GET_MOTOR_DIRECTION(iIncomingByte))
      monitorSerial.print("CCW");  
    else
      monitorSerial.print("CW ");
      
//    monitorSerial.print(GET_MOTOR_DIRECTION(iIncomingByte), DEC);

    monitorSerial.print(" Speed: ");
    monitorSerial.print(GET_MOTOR_VAL(iIncomingByte), DEC);
    monitorSerial.println("");


//    monitorSerial.print(iIncomingByte, HEX);
//    monitorSerial.print("\r\n");
*/
    motorOutput(iIncomingByte);
  }  
  
}
