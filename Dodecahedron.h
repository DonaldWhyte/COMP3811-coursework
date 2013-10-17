#ifndef DODECAHEDRON_H
#define DODECAHEDRON_H

#include "GLPlatonicSolid.h"

class Dodecahedron : public GLPlatonicSolid
{

public:
	Dodecahedron();

	const Vector3List& getVertices() const;
	const LineList& getLines() const;
	const TriangleList& getTriangles() const;

private:
	Vector3List vertices;
	LineList lines;
	TriangleList triangles;

};

#endif
