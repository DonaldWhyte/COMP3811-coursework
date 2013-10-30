#ifndef ANIMATION_SURFACE_H
#define ANIMATION_SURFACE_H

#include "../util/Geometry.h"

class Surface 
{

public:
	Surface(const VertexList& vertices, const TriangleList& triangles);
	
	const VertexList& vertices() const;
	void setVertices(const VertexList& newVertices);
	const TriangleList& triangles() const;
	void setTriangles(const TriangleList& newTriangles);

	void render();

private:
	void renderVertex(const Vertex& v);
	void renderTriangle(const Triangle& tri);
	
	VertexList verts;
	TriangleList tris;

};

#endif
