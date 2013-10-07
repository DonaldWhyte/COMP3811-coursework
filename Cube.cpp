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
