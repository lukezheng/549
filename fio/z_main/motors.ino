
#include "motor.h"


int currentDirectionBits = 0;

void motorDirectionUpdate(float pidValue)
{
	unsigned velocity = (unsigned int) MOTOR_MAX_VELOCITY*abs(pidValue);
	unsigned leftDirection = (pidValue < 0.0) ? CW: CCW;
	unsigned rightDirection = (pidValue < 0.0) ? CCW: CW;
	
	uint8_t leftMotorVal = (FRONT_LEFT << 6) | (leftDirection << 5) | (velocity);
	uint8_t rightMotorVal = (FRONT_RIGHT << 6) | (rightDirection << 5) | (velocity);
	
	motorOutput(leftMotorVal);
	motorOutput(rightMotorVal);
}

int motorOutput(int iIncomingByte)
{
  // updates only the current motor's new direction, 
  // preserving old directions of other motors
  currentDirectionBits = 
        updateDirection(currentDirectionBits, 
                        GET_MOTOR_DIRECTION(iIncomingByte), 
                        GET_MOTOR(iIncomingByte));
                        
  // sends out motor directions through I2C  
  i2cWrite(IO_EXPANDER_ADDR, currentDirectionBits);
  
  // writes out PWM
  switch (GET_MOTOR(iIncomingByte))
  {
    case VERTICAL:
      analogWrite(VERTICAL_MOTOR, GET_MOTOR_VAL(iIncomingByte)); 
      break;
      
    case SIDE:
      analogWrite(SIDE_MOTOR, GET_MOTOR_VAL(iIncomingByte));
      break;
    
    case FRONT_LEFT:
      analogWrite(FRONT_LEFT_MOTOR, GET_MOTOR_VAL(iIncomingByte));
      break;
    
    case FRONT_RIGHT:
      analogWrite(FRONT_RIGHT_MOTOR, GET_MOTOR_VAL(iIncomingByte));
      break;
      
    default:
      break;  
  }  

  return currentDirectionBits;
}

int updateDirection(int current, int direct, int motor)
{
  if (direct)
  {
    current = current | (1 << (motor*2));
    return current & ~(1 << (motor*2+1));
  }  
  else
  {
    current = current | (1 << (motor*2+1));
    return current & ~(1 << (motor*2));    
  }
}
