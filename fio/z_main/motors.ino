#include "motor.h"
#include <SoftwareSerial.h>

extern void motorDiagnostic(int);
extern SoftwareSerial monitorSerial;

void decayMotorValue(unsigned long time, float* motorThrust, float motorDecayPerSec)
{
	float dt = (time - lastDecay)/1000.0;
	if (fabs(*motorThrust) < fabs(motorDecayPerSec*dt))
		*motorThrust = 0.0;
	else
		*motorThrust -= motorDecayPerSec*dt;
}

void motorUpdate(float thetaThrust, float thetaError)
{
	float forwardThrustAdjusted = 0.0;
	
	// construct forward thrust
	if(fabs(thetaError) < minForwardThrustHeadingError)
	{
		forwardThrustAdjusted = 
				forwardThrust * (1.0 - fabs(thetaError) / minForwardThrustHeadingError);
	}

	float leftThrustAdjusted = forwardThrustAdjusted + thetaThrust;
	float rightThrustAdjusted = forwardThrustAdjusted - thetaThrust;
	float verticalThrustAdjusted = verticalThrust;
	float sideThrustAdjusted = sideThrust;
	
	leftThrustAdjusted = clamp(leftThrustAdjusted, -1.0, 1.0);
	rightThrustAdjusted = clamp(rightThrustAdjusted, -1.0, 1.0);
	verticalThrustAdjusted = clamp(verticalThrustAdjusted, -1.0, 1.0);
	sideThrustAdjusted = clamp(sideThrustAdjusted, -1.0, 1.0);
		
	// send thrusts
	motorOutput(constructMotorByte(leftThrustAdjusted, FRONT_LEFT));
	motorOutput(constructMotorByte(rightThrustAdjusted, FRONT_RIGHT));
	motorOutput(constructMotorByte(verticalThrustAdjusted, VERTICAL));
	motorOutput(constructMotorByte(sideThrustAdjusted, SIDE));	
}

uint8_t constructMotorByte(float thrust, unsigned motor)
{
	uint8_t velocity = (uint8_t) (MOTOR_MAX_VELOCITY*fabs(thrust));
	uint8_t direction = (thrust < 0.0) ? CW: CCW;

	return (motor << 6) | (direction << 5) | (velocity);
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
