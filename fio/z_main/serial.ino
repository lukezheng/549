#include <SoftwareSerial.h>
#include "constants.h"

SoftwareSerial monitorSerial(MONITOR_RX_PORT, MONITOR_TX_PORT);
int iIncomingByte = 0;
int i = 0;
int x, y, z = 0;
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
  int bytesAvailable = 0;
  
  if (monitorSerial.available())
    Serial.write(monitorSerial.read());
  if (bytesAvailable = Serial.available())
  {  
//    monitorSerial.write(iIncomingByte);
    iIncomingByte = Serial.read();

    switch (iIncomingByte)
    {
      case 'P':
        
        for (i=1; i<bytesAvailable; i++)
        {
          iIncomingByte = Serial.read();
          //motorDiagnostic(iIncomingByte);
          motorOutput(iIncomingByte);
        }
        Serial.print("P");          
        
        break;
      
      case 'M':
    
        readMagnetometer(&x, &y, &z);
        //magnetoDiagnostic(x, y, z);
        Serial.write((uint8_t*) &x, sizeof(int));
        Serial.write((uint8_t*) &y, sizeof(int));
        Serial.write((uint8_t*) &z, sizeof(int));
        
        break;
      
      default:
        break;  
    }

  }  

  
}

void magnetoDiagnostic(int x, int y, int z)
{
  monitorSerial.print("X: ");
  monitorSerial.print(x, DEC);
  monitorSerial.print(" Y: ");
  monitorSerial.print(y, DEC);
  monitorSerial.print(" Z: ");
  monitorSerial.print(z, DEC);
  monitorSerial.println();  
}

void motorDiagnostic(int iIncomingByte)
{
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
    {
      if (GET_MOTOR(iIncomingByte) & 0x01)
        monitorSerial.print("CCW ");
      else
        monitorSerial.print("CW ");  
    }
    else
    {
      if (GET_MOTOR(iIncomingByte) & 0x01)
        monitorSerial.print("CW ");
      else
        monitorSerial.print("CCW ");
    } 
//    monitorSerial.print(GET_MOTOR_DIRECTION(iIncomingByte), DEC);

    monitorSerial.print(" Speed: ");
    monitorSerial.print(GET_MOTOR_VAL(iIncomingByte), DEC);
    monitorSerial.println("");


//    monitorSerial.print(iIncomingByte, HEX);
//    monitorSerial.print("\r\n");
  
}
