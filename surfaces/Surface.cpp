#include "Surface.h"
#include <QGLWidget>

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
	glBegin(GL_TRIANGLES);
	for (TriangleList::const_iterator it = tris.begin(); (it != tris.end()); it++)
		renderTriangle(*it);
	glEnd();
}

void Surface::renderVertex(const Vertex& v)
{
	glTexCoord2f(v.texCoord.s, v.texCoord.t);
	glNormal3f(v.normal.x, v.normal.y, v.normal.z);
	glVertex3f(v.position.x, v.position.y, v.position.y);
}

void Surface::renderTriangle(const Triangle& tri)
{
	renderVertex( verts[tri.v1] );
	renderVertex( verts[tri.v2] );
	renderVertex( verts[tri.v3] );
}
