#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include "GLPlatonicSolid.h"

class Tetrahedron : public GLPlatonicSolid
{

public:
	Tetrahedron();

	const Vector3List& getVertices() const;
	const LineList& getLines() const;
	const TriangleList& getTriangles() const;

private:
	Vector3List vertices;
	LineList lines;
	TriangleList triangles;

};

#endif
