#include "Octahedron.h"

Octahedron::Octahedron()
{
	// Construct vertices, lines and triangles for a tetrahedron
	vertices.push_back( Vector3(0.0f, 0.0f, -1.0f) );
	vertices.push_back( Vector3(0.0f, -1.0f, 0.0f) );
	vertices.push_back( Vector3(1.0f, 0.0f, 0.0f) );
	vertices.push_back( Vector3(0.0f, 0.0f, 1.0f) );
	vertices.push_back( Vector3(0.0f, 0.0f, -1.0f) );
	vertices.push_back( Vector3(0.0f, 1.0f, 0.0f) );
	vertices.push_back( Vector3(-1.0f, 0.0f, 0.0f) );

	lines.push_back( Line(0, 1) ); lines.push_back( Line(1, 2) ); lines.push_back( Line(0, 2) );
	lines.push_back( Line(1, 3) ); lines.push_back( Line(2, 3) ); lines.push_back( Line(2, 5) );
	lines.push_back( Line(3, 5) ); lines.push_back( Line(2, 4) ); lines.push_back( Line(4, 5) );
	lines.push_back( Line(3, 6) ); lines.push_back( Line(5, 6) ); lines.push_back( Line(5, 4) );
	lines.push_back( Line(6, 1) ); lines.push_back( Line(6, 4) ); lines.push_back( Line(6, 4) );
	lines.push_back( Line(1, 3) );

	triangles.push_back( Triangle(0, 1, 2) );
	triangles.push_back( Triangle(3, 2, 1) );
	triangles.push_back( Triangle(3, 2, 5) );
	triangles.push_back( Triangle(5, 4, 2) );
	triangles.push_back( Triangle(6, 5, 3) );
	triangles.push_back( Triangle(4, 5, 6) );
	triangles.push_back( Triangle(1, 6, 0) );
	triangles.push_back( Triangle(6, 3, 1) );
}

const Vector3List& Octahedron::getVertices() const
{
	return vertices;
}

const LineList& Octahedron::getLines() const
{
	return lines;
}

const TriangleList& Octahedron::getTriangles() const
{
	return triangles;
}

