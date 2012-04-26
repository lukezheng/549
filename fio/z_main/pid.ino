
void initializePID(pid* p, float kp, float kd, float ki, float iLimit)
{
	p->kp = kp;
	p->kd = kd;
	p->ki = ki;
	
	p->iError = 0.0;
	p->iLimit = iLimit;

	p->oldTime = millis();
}

float pidUpdate(pid* p, 
				float error,
				float changeInError,
				unsigned long time)
{
	// time in millis OVERFLOWS in 50 days!
	float dt = (time - p->oldTime)/1000.0;
	
	p->iError += error*dt;
	
	// COME BACK to understand it
	if (fabs(p->ki * p->iError) > p->iLimit)
	{
		p->iError = (p->iError < 0.0 ? -1.0 : 1.0) / p->ki;	
	}

	float yp = p->kp * error;
	float yi = p->ki * p->iError;
	float yd = p->kd * (changeInError / dt);

	p->oldTime = time;
	
	return yp + yi + yd;
}
