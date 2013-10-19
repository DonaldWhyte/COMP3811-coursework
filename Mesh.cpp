#include <QGLWidget>
#include "Mesh.h"
#include "Matrix44.h"

Mesh::~Mesh()
{
}

const VertexList& Mesh::vertices() const
{
	return verts;
}

void Mesh::setVertices(const VertexList& newVerts)
{
	verts = newVerts;
}

const TriangleList& Mesh::triangles() const
{
	return tris;
}

void Mesh::setTriangles(const TriangleList& newTris)
{
	tris = newTris;
}

void Mesh::renderVertex(const Vertex& v)
{
	glNormal3f(v.normal.x, v.normal.y, v.normal.z);
	glVertex3f(v.position.x, v.position.y, v.position.y);
}

void Mesh::render()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Perform local model transformations on mesh
	Matrix44 transformation = transformation * Matrix44::translation(pos.x, pos.y, pos.z);
	transformation = transformation * Matrix44::xyzRotation(rot);
	// Compute transformed vertices
	VertexList transformedVerts;
	transformedVerts.reserve( verts.size() );
	for (VertexList::const_iterator it = verts.begin(); (it != verts.end()); it++)
	{
		Vertex newVert = (*it);//{ transformation * it->position, transformation * it->normal };
		transformedVerts.push_back(newVert);
	}
	
	// Draw the vertex on the screen
	glBegin(GL_TRIANGLES);
	for (TriangleList::const_iterator it = tris.begin(); (it != tris.end()); it++)
	{
		renderVertex( transformedVerts[it->v1] );
		renderVertex( transformedVerts[it->v2] );
		renderVertex( transformedVerts[it->v3] );
	}
	glEnd();

	glPopMatrix();
}
