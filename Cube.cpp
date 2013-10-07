#include "Cube.h"

Cube::Cube()
{
	// Create cube's vertices, lines and trinagles
	vertices.reserve(8);
	vertices.push_back( Vector3(-1.0f, -1.0f, -1.0f) );
	vertices.push_back( Vector3(-1.0f, -1.0f, 1.0f) );
	vertices.push_back( Vector3(-1.0f, 1.0f, -1.0f) );
	vertices.push_back( Vector3(-1.0f, 1.0f, 1.0f) );
	vertices.push_back( Vector3(1.0f, -1.0f, -1.0f) );
	vertices.push_back( Vector3(1.0f, -1.0f, 1.0f) );
	vertices.push_back( Vector3(1.0f, 1.0f, -1.0f) );
	vertices.push_back( Vector3(1.0f, 1.0f, 1.0f) );

	lines.reserve(12);
	lines.push_back( Line(0, 1) ); lines.push_back( Line(1, 3) );
	lines.push_back( Line(3, 2) ); lines.push_back( Line(2, 0) );
	lines.push_back( Line(0, 4) ); lines.push_back( Line(1, 5) );
	lines.push_back( Line(3, 7) ); lines.push_back( Line(2, 6) );
	lines.push_back( Line(4, 5) ); lines.push_back( Line(5, 7) );
	lines.push_back( Line(7, 6) ); lines.push_back( Line(6, 4) );

	triangles.reserve(12);
	triangles.push_back( Triangle(0, 1, 3) );
	triangles.push_back( Triangle(0, 3, 2) );
	triangles.push_back( Triangle(0, 1, 4) );
	triangles.push_back( Triangle(1, 4, 5) );
	triangles.push_back( Triangle(0, 2, 4) );
	triangles.push_back( Triangle(2, 6, 4) );
	triangles.push_back( Triangle(5, 4, 6) );
	triangles.push_back( Triangle(5, 6, 7) );
	triangles.push_back( Triangle(2, 3, 7) );
	triangles.push_back( Triangle(2, 7, 6) );
	triangles.push_back( Triangle(1, 5, 7) );
	triangles.push_back( Triangle(1, 7, 3) );
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
