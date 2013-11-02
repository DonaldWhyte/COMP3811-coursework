#include "Geometry.h"

const double PI = 3.14159265358979323846;

float degreesToRadians(float degrees)
{
	return degrees * (PI / 180.0f);
}

float radiansToDegrees(float radians)
{
    return radians * (180.0f / PI);
}
