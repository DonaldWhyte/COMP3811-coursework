#ifndef MATH_MATRIX44_H
#define MATH_MATRIX44_H

#include "Vector3.h"

class Matrix44
{

public:
	Matrix44(); // constructs ZERO matrix
	Matrix44(float** elements);
	Matrix44(float elements[4][4]);

	const float* rowMajorData() const;
	const float* columnMajorData() const;
	const float* operator[](int row) const;
	float* operator[](int row);
	float operator()(int row, int col) const; // just for getting values
	float& operator()(int row, int col); // for setting values

	// Matrix operations
	Matrix44 operator*(const Matrix44& mat) const;

	// Vector3 operations (just treats fourth element of vector as 1)
	Vector3 operator*(const Vector3& vec) const;

	// Factory methods
	static Matrix44 identity();
	static Matrix44 translation(float x, float y, float z);
	static Matrix44 translation(const Vector3& amount);
	static Matrix44 scale(float x, float y, float z);
	static Matrix44 scale(const Vector3& amount);
	static Matrix44 xRotation(float degrees);
	static Matrix44 yRotation(float degrees);
	static Matrix44 zRotation(float degrees);
	static Matrix44 xyzRotation(const Vector3& rotationVec);

private:
	static const int ROWS = 4;
	static const int COLUMNS = 4;

	float elements[ROWS][COLUMNS];

};

#endif
