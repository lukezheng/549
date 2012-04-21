typedef struct 
{
	float kp;
	float ki;
	float kd;
	
	float iError;
	float iLimit;
	
	float oldError;
	unsigned long oldTime;
} pid;