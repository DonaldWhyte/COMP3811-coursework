#ifndef MESH_H
#define MESH_H

#include "Drawable.h"
#include "Geometry.h"

class Mesh : public Drawable
{

public:
	enum Colouring
	{
		MESH_COLOUR_SAME = 0,
		MESH_ALTERNATING_TRIANGLES,
		MESH_FLAT_SHADING,
		MESH_SMOOTH_SHADING,
		MESH_TEXTURE
	};

	virtual ~Mesh();

	const VertexList& vertices() const;
	void setVertices(const VertexList& newVerts);
	const TriangleList& triangles() const;
	void setTriangles(const TriangleList& triangles); 
	Colouring colouring() const;
	void setColouring(Colouring newColouring);

	void renderVertex(const Vertex& v);
	void renderTriangle(const VertexList& verticesToUse, const Triangle& tri);
	void renderPoints(const VertexList& vertices);
	void renderNormals(const VertexList& vertices);
	void render();

private:
	static const float NORMAL_SCALING_FACTOR = 0.05f;

	VertexList verts;
	TriangleList tris;
	Colouring triangleColouring;

};

#endif
