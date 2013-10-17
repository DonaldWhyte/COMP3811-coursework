#ifndef ISOCAHEDRON_H
#define ISOCAHEDRON_H

#include "GLPlatonicSolid.h"

class Isocahedron : public GLPlatonicSolid
{

public:
	Isocahedron();

	const Vector3List& getVertices() const;
	const LineList& getLines() const;
	const TriangleList& getTriangles() const;

private:
	Vector3List vertices;
	LineList lines;
	TriangleList triangles;

};

#endif
