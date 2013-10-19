#ifndef MESH_H
#define MESH_H

#include "Drawable.h"
#include "Geometry.h"

class Mesh : public Drawable
{

public:
	virtual ~Mesh();

	const VertexList& vertices() const;
	void setVertices(const VertexList& newVerts);
	const TriangleList& triangles() const;
	void setTriangles(const TriangleList& triangles); 

	void renderVertex(const Vertex& v);
	void render();

private:
	VertexList verts;
	TriangleList tris;

};

#endif
