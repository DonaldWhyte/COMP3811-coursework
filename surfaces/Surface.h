#ifndef ANIMATION_SURFACE_H
#define ANIMATION_SURFACE_H

#include "../util/Geometry.h"

class Surface 
{

public:
	Surface(const VertexList& vertices, const TriangleList& triangles,
	    const Vector3& colour = Vector3(1.0f, 0.0f, 0.0f));
	
	const VertexList& vertices() const;
	void setVertices(const VertexList& newVertices);
	const TriangleList& triangles() const;
	void setTriangles(const TriangleList& newTriangles);
	const Vector3& colour() const;
    void setColour(const Vector3& newColour);

	
	bool showingPoints() const;
	void setShowPoints(bool showPoints);
	bool showingLines() const;
	void setShowLines(bool showLines);

	void render();

private:
	void renderVertex(const Vertex& v);
	void renderTriangle(const Triangle& tri);
	
	VertexList verts;
	TriangleList tris;
	Vector3 surfaceColour;
	bool showPoints;
	bool showLines;	

};

#endif
