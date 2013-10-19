#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <vector>
#include <iostream>

class Vector3
{

public:
	Vector3();
	Vector3(float x, float y, float z);

	float x;
	float y;
	float z;
};

// For pretty printing
std::ostream& operator<<(std::ostream& os, const Vector3& vec);

typedef std::vector<Vector3> Vector3List;

#endif 
