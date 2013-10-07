#ifndef GEOMETRY_CUBE_H
#define GEOMETRY_CUBE_H

#include "GLPlatonicSolid.h"

class Cube : public GLPlatonicSolid
{

public:
	Cube();

        virtual const Vector3List& getVertices() const;
        virtual const LineList& getLines() const;
        virtual const TriangleList& getTriangles() const;

private:
	Vector3List vertices;
	LineList lines;
	TriangleList triangles;

};

#endif
