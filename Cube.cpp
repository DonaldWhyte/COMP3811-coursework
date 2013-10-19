#include "Cube.h"

Cube::Cube()
{
	// Create cube's vertices, lines and trinagles
	vertices.reserve(8);
	vertices.push_back( Vector3(-1.0f, -1.0f, 1.0f) );
	vertices.push_back( Vector3(1.0f, -1.0f, 1.0f) );
	vertices.push_back( Vector3(1.0f, 1.0f, 1.0f) );
	vertices.push_back( Vector3(-1.0f, 1.0f, 1.0f) );
	vertices.push_back( Vector3(-1.0f, -1.0f, -1.0f) );
	vertices.push_back( Vector3(1.0f, -1.0f, -1.0f) );
	vertices.push_back( Vector3(1.0f, 1.0f, -1.0f) );
	vertices.push_back( Vector3(-1.0f, 1.0f, -1.0f) );

	lines.reserve(12);
	lines.push_back( Line(0, 1) );
	lines.push_back( Line(1, 2) );
	lines.push_back( Line(4, 7) );
	lines.push_back( Line(2, 6) );
	lines.push_back( Line(6, 7) );
	lines.push_back( Line(1, 5) );
	lines.push_back( Line(4, 5) );
	lines.push_back( Line(5, 6) );
	lines.push_back( Line(2, 3) );
	lines.push_back( Line(0, 4) );
	lines.push_back( Line(3, 7) );
	lines.push_back( Line(0, 3) );

	triangles.reserve(12);
	triangles.push_back( Triangle(0, 1, 3) );
	triangles.push_back( Triangle(1, 2, 3) );
	triangles.push_back( Triangle(5, 4, 6) );
	triangles.push_back( Triangle(4, 7, 6) );
	triangles.push_back( Triangle(1, 5, 2) );
	triangles.push_back( Triangle(5, 6, 2) );
	triangles.push_back( Triangle(4, 0, 7) );
	triangles.push_back( Triangle(0, 3, 7) );
	triangles.push_back( Triangle(5, 4, 1) );
	triangles.push_back( Triangle(4, 0, 1) );
	triangles.push_back( Triangle(3, 2, 7) );
	triangles.push_back( Triangle(2, 6, 7) );
}

const Vector3List& Cube::getVertices() const
{
	return vertices;
}

const LineList& Cube::getLines() const
{
	return lines;
}

const TriangleList& Cube::getTriangles() const
{
	return triangles;
}
