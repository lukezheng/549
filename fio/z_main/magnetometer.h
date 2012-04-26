#define X_OFFSET	7
#define Y_OFFSET	57	
#define X_SCALE		1.0
#define Y_SCALE		1.068627451
#define DECLINATION	-9.23

// raw x, y, z value readings
int magneto[3];

// in radians
float targetDirection = 0.0;
float currentDirection = 0.0;

float thetaError = 0.0;
float thetaOldError = 0.0;
float thetaChangeInError = 0.0;

// for control
float thetaPIDVal = 0.0;