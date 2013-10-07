#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <vector>

class Vector3
{

public:
	Vector3();
	Vector3(float x, float y, float z);

	float x;
	float y;
	float z;

};

typedef std::vector<Vector3> Vector3List;

#endif 
