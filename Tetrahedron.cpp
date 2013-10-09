#include "Tetrahedron.h"

Tetrahedron::Tetrahedron()
{
	// Construct vertices, lines and triangles for a tetrahedron
	// TODO
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

