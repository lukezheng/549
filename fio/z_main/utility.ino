
#include <Math.h>

float clamp(float value, float min, float max)
{
	return max(min, min(value, max));
}

void bytesToType4(int byteVal, int pos, float* val)
{
	*((uint8_t*) ((int) val + pos)) = byteVal;
}