typedef struct 
{
	float kp;
	float ki;
	float kd;
	
	float iError;
	float iLimit;

	unsigned long oldTime;
} pid;