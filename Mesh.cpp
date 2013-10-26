#include <QGLWidget>
#include "Mesh.h"
#include "Matrix44.h"
#include "Common.h"

Mesh::Mesh() : triangleColouring(MESH_COLOUR_SAME), geomType(MESH_GEOM_TRIANGLES),
	surfaceTexture(NULL), useSurfaceNormals(false)
{
}

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

Mesh::GeometryType Mesh::geometryType() const
{
	return geomType;
}

void Mesh::setGeometryType(Mesh::GeometryType newGeomType)
{
	geomType = newGeomType;
}

bool Mesh::showingNormals() const
{
	return drawNormals;
}

void Mesh::showNormals(bool willShow)
{
	drawNormals = willShow;
}

Texture* Mesh::texture() const
{
	return surfaceTexture;
}

void Mesh::setTexture(Texture* newTexture)
{
	surfaceTexture = newTexture;
}


bool Mesh::usingPerFaceNormals() const
{
	return useSurfaceNormals;
}

void Mesh::setPerFaceNormals(bool usePerFace)
{
	useSurfaceNormals = usePerFace;
}

void Mesh::renderVertex(const Vertex& v)
{
	glTexCoord2f(v.texCoord.s, v.texCoord.t);
	glNormal3f(v.normal.x, v.normal.y, v.normal.z);
	glVertex3f(v.position.x, v.position.y, v.position.y);
}

void Mesh::renderTriangle(const VertexList& verticesToUse, const Triangle& tri)
{
	renderVertex( verticesToUse[tri.v1] );
	renderVertex( verticesToUse[tri.v2] );
	renderVertex( verticesToUse[tri.v3] );
}

void Mesh::renderPoints(const VertexList& vertices)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
		for (VertexList::const_iterator it = vertices.begin(); (it != vertices.end()); it++)
			glVertex3f(it->position.x, it->position.y, it->position.x);
	glEnd();
}

void Mesh::renderLines(const VertexList& vertices, const TriangleList& triangles)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		for (TriangleList::const_iterator it = triangles.begin(); (it != triangles.end()); it++)
		{
			const Vertex& v1 = vertices[it->v1];
			const Vertex& v2 = vertices[it->v2];
			const Vertex& v3 = vertices[it->v3];
			glVertex3f(v1.position.x, v1.position.y, v1.position.x);
			glVertex3f(v2.position.x, v2.position.y, v2.position.x);
			glVertex3f(v2.position.x, v2.position.y, v2.position.x);
			glVertex3f(v3.position.x, v3.position.y, v3.position.x);
			glVertex3f(v3.position.x, v3.position.y, v3.position.x);
			glVertex3f(v1.position.x, v1.position.y, v1.position.x);
		}
	glEnd();
}

void Mesh::renderTriangles(const VertexList& vertices, const TriangleList& triangles)
{
	glBegin(GL_TRIANGLES);
	if (triangleColouring == MESH_ALTERNATING_TRIANGLES)
	{
		// Whole for-loop put it if-statement so there isn't a branch every iteration (costly operation
		for (unsigned int i = 0; (i < triangles.size()); i++)
		{
			const Vector3& col = ALTERNATING_TRIANGLE_COLOURS[i % NUM_ALTERNATING_COLOURS];
			glColor3f(col.x, col.y, col.y);
			renderTriangle(vertices, tris[i]);
		}
	}
	else
	{
		for (TriangleList::const_iterator it = triangles.begin(); (it != triangles.end()); it++)	
			renderTriangle(vertices, *it);
	}
	glEnd();
}

void Mesh::renderNormals(const VertexList& vertices)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		for (VertexList::const_iterator it = vertices.begin(); (it != vertices.end()); it++)
		{
			const Vector3& position = it->position;
			const Vector3& normal = it->normal;
			Vector3 end = position + (normal * NORMAL_SCALING_FACTOR);
			glVertex3f(it->position.x, it->position.y, it->position.z);
			glVertex3f(end.x, end.y, end.y);	
		}
	glEnd();
}

void Mesh::render()
{
	// If texturing has been enabled, ensure we set the correct OpenGL state
	if (triangleColouring == MESH_TEXTURE)
	{
		// If texture hasn't been loaded yet - load it now!
		// This is lazy initialisation
		if (!surfaceTexture)
			surfaceTexture = new Texture("resources/world_texture.jpg");
		glEnable(GL_TEXTURE_2D);
		surfaceTexture->bind();
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Perform local model transformations on mesh
	Matrix44 transformation =  Matrix44::translation(pos.x, pos.y, pos.z);
	transformation = transformation * Matrix44::xyzRotation(rot);
	// Transform vertices using position and orientation of drawable
	VertexList transformedVerts = verts;
	// If using per-face normals and not per-vertex normals, compute surface normals now
	if (useSurfaceNormals)
	{
		Vector3List surfaceNormals = computeSurfaceNormals(transformedVerts, tris);
		for (int i = 0; (i < surfaceNormals.size()); i++)
		{
			transformedVerts[i].normal = surfaceNormals[i];
		}
	}
	for (VertexList::iterator it = transformedVerts.begin(); (it != transformedVerts.end()); it++)
	{
		it->position = transformation * it->position;
		it->normal = (transformation * it->normal).normalise();
	}

	// How mesh is drawn depends on geometry type chosen
	switch (geomType)
	{
	case MESH_GEOM_POINTS:
		renderPoints(transformedVerts);
		break;
	case MESH_GEOM_LINES:
		renderLines(transformedVerts, tris);
		break;
	case MESH_GEOM_TRIANGLES:
		renderTriangles(transformedVerts, tris);
		break;
	}
	// Also draw lines reprensenting vertex normals
	if (drawNormals)
	{
		renderNormals(transformedVerts);
	}

	glPopMatrix();

	// Make sure the mesh's texture is unbinded after rendering
	if (triangleColouring == MESH_TEXTURE)
	{
		if (surfaceTexture)
			surfaceTexture->unbind();
		glDisable(GL_TEXTURE_2D);
	}
}

Vector3List Mesh::computeSurfaceNormals(const VertexList& vertices, const TriangleList& triangles)
{
	Vector3List normals;
	normals.resize(vertices.size());

	for (TriangleList::const_iterator it = triangles.begin();
		(it != triangles.end()); it++)
	{
		// Get two points of the triangle and create two vectors from them (sides of triangle)
		Vector3 s1 = vertices[it->v2].position - vertices[it->v1].position;
		Vector3 s2 = vertices[it->v3].position - vertices[it->v1].position;
		// Compute cross product of sides to get surface normal
		Vector3 surfaceNormal = s1.cross(s2).normalise();
		// Assign this surface normal to all v
		normals[it->v1] = surfaceNormal;
		normals[it->v2] = surfaceNormal;
		normals[it->v3] = surfaceNormal;
	}

	return normals;
}
