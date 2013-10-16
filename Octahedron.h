#ifndef OCTAHEDRON_H
#define OCTAHEDRON_H

#include "GLPlatonicSolid.h"

class Octahedron : public GLPlatonicSolid
{

public:
	Octahedron();

	const Vector3List& getVertices() const;
	const LineList& getLines() const;
	const TriangleList& getTriangles() const;

private:
	Vector3List vertices;
	LineList lines;
	TriangleList triangles;

};

#endif
