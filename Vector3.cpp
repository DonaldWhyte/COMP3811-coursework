#include "Vector3.h"
#include <math.h>

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f)
{
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3 Vector3::negate() const
{
	return Vector3(-x, -y, -z);
}

float Vector3::length() const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3::sqrLength() const
{
	return (x * x + y * y + z * z);
}

Vector3 Vector3::normalise() const
{
	float len = length();
	return Vector3(x / len, y / len, z / len);
}

std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
	os << vec.x << "," << vec.y << "," << vec.z;
	return os;
}
