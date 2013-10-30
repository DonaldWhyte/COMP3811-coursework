#include "Surface.h"

Surface::Surface(const VertexList& vertices, const TriangleList& triangles) :
	verts(vertices), tris(triangles)
{
}

const VertexList& Surface::vertices() const
{
	return verts;
}

void Surface::setVertices(const VertexList& newVertices)
{
	verts = newVertices;
}

const TriangleList& Surface::triangles() const
{
	return tris;
}

void Surface::setTriangles(const TriangleList& newTriangles)
{
	tris = newTriangles;
}

void Surface::render()
{
	// TODO
}
