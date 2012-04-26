#include <SoftwareSerial.h>		
	
extern float targetDirection;
extern float currentDirection;
extern int magneto[3];
extern float thetaError;
extern float thetaOldError;
extern float thetaChangeInError;
extern float thetaPIDVal;
extern unsigned long lastDecay;

extern float minForwardThrustHeadingError;
extern float forwardThrust;
extern float forwardDecayPerSec;
extern float verticalThrust;
extern float verticalDecayPerSec;
extern float sideThrust;
extern float sideDecayPerSec;

extern SoftwareSerial monitorSerial;

void control()
{
	readMagnetometer(magneto, magneto+1, magneto+2);	
			
			
//	monitorSerial.print("control() Target Direction: ");		
//	monitorSerial.println(targetDirection, DEC);		
			
//	monitorSerial.print("control() Current Direction: ");
//	monitorSerial.println(currentDirection, DEC);
	
	
	// normalize theta
	thetaError = normalizeTheta(targetDirection - currentDirection);
	thetaChangeInError = normalizeTheta(thetaError - thetaOldError);
	
	// pid control for heading
	thetaPIDVal = pidUpdate(&headingPID, thetaError, thetaChangeInError, millis());  
		
//	monitorSerial.print("control() thetaPIDVal before clamp: ");
//	monitorSerial.println(thetaPIDVal, DEC);
	
	thetaPIDVal = clamp(thetaPIDVal, -0.5, 0.5);
	
//	monitorSerial.print("control() thetaPIDVal after clamp: ");
//	monitorSerial.println(thetaPIDVal, DEC);
	
	// decay motor values
	decayMotorValue(millis(), &forwardThrust, forwardDecayPerSec);
	decayMotorValue(millis(), &verticalThrust, verticalDecayPerSec);
	decayMotorValue(millis(), &sideThrust, sideDecayPerSec);
	lastDecay = millis();
	
	// motor output
	motorUpdate(thetaPIDVal, thetaError);

	thetaOldError = thetaError;
}