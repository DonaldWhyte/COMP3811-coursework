#include "Surface.h"
#include <QGLWidget>

// Functions only used in this translation unit - don't need to be in header!
void renderPoints(const VertexList& vertices)
{
	glBegin(GL_POINTS);
	for (VertexList::const_iterator v = vertices.begin(); (v != vertices.end()); v++)
		glVertex3fv(v->position.elems);
	glEnd();

}
void renderLines(const VertexList& vertices, const TriangleList& triangles)
{
        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_LINES);
                for (TriangleList::const_iterator it = triangles.begin(); (it != triangles.end()); it++)
                {
                        const Vertex& v1 = vertices[it->v1];
                        const Vertex& v2 = vertices[it->v2];
                        const Vertex& v3 = vertices[it->v3];
                        glVertex3fv(v1.position.elems);
                        glVertex3fv(v2.position.elems);
                        glVertex3fv(v2.position.elems);
                        glVertex3fv(v3.position.elems);
                        glVertex3fv(v3.position.elems);                                                                                                
                        glVertex3fv(v1.position.elems);                                                                                                                     
                }
        glEnd();
}



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
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	for (TriangleList::const_iterator it = tris.begin(); (it != tris.end()); it++)
		renderTriangle(*it);
    glEnd();
}

void Surface::renderVertex(const Vertex& v)
{
	glTexCoord2f(v.texCoord.s, v.texCoord.t);
	glNormal3fv(v.normal.elems);
	glVertex3fv(v.position.elems);
}

void Surface::renderTriangle(const Triangle& tri)
{
	renderVertex( verts[tri.v1] );
	renderVertex( verts[tri.v2] );
	renderVertex( verts[tri.v3] );
}

