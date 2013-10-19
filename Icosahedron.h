#ifndef ISOCAHEDRON_H
#define ISOCAHEDRON_H

#include "GLPlatonicSolid.h"

class Icosahedron : public GLPlatonicSolid
{

public:
	Icosahedron();

	const Vector3List& getVertices() const;
	const LineList& getLines() const;
	const TriangleList& getTriangles() const;

private:
	Vector3List vertices;
	LineList lines;
	TriangleList triangles;

};

#endif
