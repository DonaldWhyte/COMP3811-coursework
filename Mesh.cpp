#include <QGLWidget>
#include "Mesh.h"
#include "Matrix44.h"
#include "Common.h"

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

Mesh::Colouring Mesh::colouring() const
{
	return triangleColouring;
}

void Mesh::setColouring(Mesh::Colouring newColouring)
{
	triangleColouring = newColouring;
}

void Mesh::renderVertex(const Vertex& v)
{
	glNormal3f(v.normal.x, v.normal.y, v.normal.z);
	glVertex3f(v.position.x, v.position.y, v.position.y);
}

void Mesh::renderTriangle(const VertexList& verticesToUse, const Triangle& tri)
{
	renderVertex( verticesToUse[tri.v1] );
	renderVertex( verticesToUse[tri.v2] );
	renderVertex( verticesToUse[tri.v3] );
}

void Mesh::render()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Perform local model transformations on mesh
	Matrix44 transformation =  Matrix44::translation(pos.x, pos.y, pos.z);
	transformation = transformation * Matrix44::xyzRotation(rot);
	// Compute transformed vertices
	VertexList transformedVerts;
	transformedVerts.reserve( verts.size() );
	for (VertexList::const_iterator it = verts.begin(); (it != verts.end()); it++)
	{
		Vertex newVert;
		newVert.position = transformation * it->position;
		newVert.normal = transformation * it->normal;
		transformedVerts.push_back(newVert);
	}
	
	/*glBegin(GL_POINTS);
		for (VertexList::const_iterator it = transformedVerts.begin(); (it != transformedVerts.end()); it++)
			glVertex3f(it->position.x, it->position.y, it->position.x);
	glEnd();
	return;*/

	// Specify mesh's surface material
	// TODO: put these colours somewhere else
	float greyColour[4] = { 0.4f, 0.8f, 0.4f, 1.0f };
	float whiteColour[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, greyColour);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteColour);
	// Draw the vertex on the screen
	glBegin(GL_TRIANGLES);
	if (triangleColouring == MESH_ALTERNATING_TRIANGLES)
	{
		// Whole for-loop put it if-statement so there isn't a branch every iteration (costly operation)
		for (unsigned int i = 0; (i < tris.size()); i++)
		{
			const Vector3& col = ALTERNATING_TRIANGLE_COLOURS[i % NUM_ALTERNATING_COLOURS];
			glColor3f(col.x, col.y, col.y);
			renderTriangle(transformedVerts, tris[i]);
		}
	}
	else
	{
		for (TriangleList::const_iterator it = tris.begin(); (it != tris.end()); it++)	
			renderTriangle(transformedVerts, *it);
	}
	glEnd();

	glPopMatrix();
}
