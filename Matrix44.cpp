#include "Matrix44.h"

Matrix44::Matrix44()
{
	for (int i = 0; (i < ROWS); i++)
		for (int j = 0; (j < COLUMNS); j++)
			elements[i][j] = 0.0f;
}

Matrix44::Matrix44(float** elements)
{
	for (int i = 0; (i < ROWS); i++)
		for (int j = 0; (j < COLUMNS); j++)
			this->elements[i][j] = elements[i][j];
}

Matrix44::Matrix44(float elements[4][4])
{
	for (int i = 0; (i < ROWS); i++)
		for (int j = 0; (j < COLUMNS); j++)
			this->elements[i][j] = elements[i][j];
}

const float* Matrix44::operator[](int row) const
{
	return elements[row];
}

float* Matrix44::operator[](int row)
{
	return elements[row];
}

float Matrix44::operator()(int row, int col) const
{
	return elements[row][col];
}

float& Matrix44::operator()(int row, int col)
{
	return elements[row][col];
}

Matrix44 Matrix44::operator*(const Matrix44& mat) const
{
	float result[4][4] = { { 0.0f } };
	for (int i = 0; (i < ROWS); i++)
		for (int j = 0; (j < COLUMNS); j++)
			result[i][j] = (elements[i][0] * mat[0][j]) + (elements[i][1] * mat[1][j]) + (elements[i][2] * mat[2][j]) + (elements[i][3] * mat[3][j]);
	return Matrix44(result);
}

Vector3 Matrix44::operator*(const Vector3& vec) const
{
	// NOTE: We ignore the FOURTH ROW AND COLUMN of the matrix
	// and just use the 3x3 part for 3D vector multiplication
	float x = elements[0][0] * vec.x + elements[0][1] * vec.y + elements[0][2] * vec.z;
	float y = elements[1][0] * vec.x + elements[1][1] * vec.y + elements[1][2] * vec.z;
	float z = elements[2][0] * vec.x + elements[2][1] * vec.y + elements[2][2] * vec.z;
	return Vector3(x, y, z);
}

Matrix44 Matrix44::identity()
{
	float elements[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	return Matrix44(&elements[0]);
}
