//#include "pid.h"

void initializePID(pid* p, float kp, float kd, float ki, float iLimit)
{
	p->kp = kp;
	p->kd = kd;
	p->ki = ki;
	
	p->iLimit = iLimit;
}

float pidUpdate(pid* p, 
				float current, 
				float target, 
				unsigned long time)
{
	float dt = time - p->oldTime;
	float error = target - current;
	
	p->iError += error*dt;
	
	// COME BACK to understand it
	if (abs(p->ki*p->iError) > p->iLimit)
	{
		p->iError = (p->iError < 0.0 ? -1.0 : 1.0) / p->ki;	
	}

	float yp = p->kp * error;
	float yi = p->ki * p->iError;
	float yd = p->kd * (error - p->oldError) / dt;
	
	p->oldError = error;
	p->oldTime = time;
	
	return yp + yi + yd;
}