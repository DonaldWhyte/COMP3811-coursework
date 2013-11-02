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

float Vector3::dot(const Vector3& vec) const
{
	return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::cross(const Vector3& vec) const
{
	return Vector3(y * vec.z - z * vec.y,
		z * vec.x - x * vec.z,
		x * vec.y - y * vec.x);
}

Vector3 Vector3::lerp(const Vector3& vec, float t) const
{
    return Vector3((1 - t) * x + t * vec.x,
		(1 - t) * y + t * vec.y,
		(1 - t) * z + t * vec.z);
}

Vector3 operator +(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x + b.x, a.y + a.y, a.z + b.z);
}

Vector3 operator -(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3 operator *(const Vector3& vec, float scalar)
{
	return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
	os << vec.x << "," << vec.y << "," << vec.z;
	return os;
}
