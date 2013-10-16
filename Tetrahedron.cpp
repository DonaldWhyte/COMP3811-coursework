#include "Tetrahedron.h"

Tetrahedron::Tetrahedron()
{
	// Construct vertices, lines and triangles for a tetrahedron
	vertices.push_back( Vector3(-1.0f, -1.0f, -1.0f) );
	vertices.push_back( Vector3(1.0f, -1.0f, 1.0f) );
	vertices.push_back( Vector3(-1.0f, 1.0f, 1.0f) );
	vertices.push_back( Vector3(1.0f, 1.0f, -1.0f) );
	lines.push_back( Line(0, 1) ); lines.push_back( Line(1, 2) ); lines.push_back( Line(2, 0) ); // bottom lines
	lines.push_back( Line(0, 3) ); lines.push_back( Line(1, 3) ); lines.push_back( Line(2, 3) ); // lines going to tip
	triangles.push_back( Triangle(0, 1, 2) );
	triangles.push_back( Triangle(3, 0, 1) );
	triangles.push_back( Triangle(3, 1, 2) );
	triangles.push_back( Triangle(3, 2, 0) );
}

const Vector3List& Tetrahedron::getVertices() const
{
	return vertices;
}

const LineList& Tetrahedron::getLines() const
{
	return lines;
}

const TriangleList& Tetrahedron::getTriangles() const
{
	return triangles;
}

