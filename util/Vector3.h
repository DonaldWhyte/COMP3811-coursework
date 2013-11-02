#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <vector>
#include <iostream>

class Vector3
{

public:
	Vector3();
	Vector3(float x, float y, float z);

	Vector3 negate() const;
	float length() const;
	float sqrLength() const;
	Vector3 normalise() const;
	 
	float dot(const Vector3& vec) const;
	Vector3 cross(const Vector3& vec) const;
	
	Vector3 lerp(const Vector3& vec, float t) const;
	Vector3 slerp(const Vector3& vec, float t) const;

	union 
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float elems[3];
	};
};

Vector3 operator +(const Vector3& a, const Vector3& b);
Vector3 operator -(const Vector3& a, const Vector3& b);
Vector3 operator *(const Vector3& vec, float scalar);

// For pretty printing
std::ostream& operator<<(std::ostream& os, const Vector3& vec);

typedef std::vector<Vector3> Vector3List;

#endif 
