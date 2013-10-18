#include <math.h>
#include "Isocahedron.h"

// Pre-computed for performance
static const float PHI = 1.25663706144; 

Isocahedron::Isocahedron()
{
	vertices.push_back( Vector3(-1.0f, 0.0f, 0.0f) );
	vertices.push_back( Vector3(-0.707106f, -0.707106f, 0.0f) );
	vertices.push_back( Vector3(-0.707106f, 0.0f, -0.707106f) );
	vertices.push_back( Vector3(-0.707106f, 0.0f, 0.707106f) );
	vertices.push_back( Vector3(-0.707106f, 0.707106f, 0.0f) );
	vertices.push_back( Vector3(0.0f, -1.0f, 0.0f) );
	vertices.push_back( Vector3(0.0f, -0.707106f, -0.707106f) );
	vertices.push_back( Vector3(0.0f, -0.707106f, 0.707106f) );
	vertices.push_back( Vector3(0.0f, 0.0f, -1.0f) );
	vertices.push_back( Vector3(0.0f, 0.0f, 1.0f) );
	vertices.push_back( Vector3(0.0f, 0.707106f, -0.707106f) );
	vertices.push_back( Vector3(0.0f, 0.707106f, 0.707106f) );
	vertices.push_back( Vector3(0.0f, 1.0f, 0.0f) );
	vertices.push_back( Vector3(0.707106f, -0.707106f, 0.0f) );
	vertices.push_back( Vector3(0.707106f, 0.0f, -0.707106f) );
	vertices.push_back( Vector3(0.707106f, 0.0f, 0.707106f) );
	vertices.push_back( Vector3(0.707106f, 0.707106f, 0.0f) );
	vertices.push_back( Vector3(1.0f, 0.0f, 0.0f) );

	triangles.push_back( Triangle(0, 2, 1) );
	triangles.push_back( Triangle(0, 4, 2) );
	triangles.push_back( Triangle(1, 6, 5) );
	triangles.push_back( Triangle(1, 3, 0) );
	triangles.push_back( Triangle(1, 7, 3) );
	triangles.push_back( Triangle(2, 6, 1) );
	triangles.push_back( Triangle(2, 8, 6) );
	triangles.push_back( Triangle(2, 10, 8) );
	triangles.push_back( Triangle(3, 4, 0) );
	triangles.push_back( Triangle(3, 11, 4) );
	triangles.push_back( Triangle(4, 10, 2) );
	triangles.push_back( Triangle(4, 12, 10) );
	triangles.push_back( Triangle(5, 13, 7) );
	triangles.push_back( Triangle(5, 7, 1) );
	triangles.push_back( Triangle(6, 14, 13) );
	triangles.push_back( Triangle(6, 13, 5) );
	triangles.push_back( Triangle(7, 15, 9) );
	triangles.push_back( Triangle(7, 9, 3) );
	triangles.push_back( Triangle(9, 11, 3) );
	triangles.push_back( Triangle(8, 14, 6) );
	triangles.push_back( Triangle(10, 14, 8) );
	triangles.push_back( Triangle(9, 15, 11) );
	triangles.push_back( Triangle(11, 12, 4) );
	triangles.push_back( Triangle(10, 16, 14) );
	triangles.push_back( Triangle(15, 16, 11) );
	triangles.push_back( Triangle(13, 15, 7) );
	triangles.push_back( Triangle(12, 16, 10) );
	triangles.push_back( Triangle(11, 16, 12) );
	triangles.push_back( Triangle(13, 17, 15) );
	triangles.push_back( Triangle(14, 17, 13) );
	triangles.push_back( Triangle(16, 17, 14) );
	triangles.push_back( Triangle(15, 17, 16) );    
}

const Vector3List& Isocahedron::getVertices() const
{
	return vertices;
}

const LineList& Isocahedron::getLines() const
{
	return lines;
}

const  TriangleList& Isocahedron::getTriangles() const
{
	return triangles;
}

