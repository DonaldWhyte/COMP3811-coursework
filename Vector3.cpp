#include "Vector3.h"

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f)
{
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}


std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
	os << vec.x << "," << vec.y << "," << vec.z;
	return os;
}
