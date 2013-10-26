#ifndef GL_TORUS_H
#define GL_TORUS_H

#include "Mesh.h"

/* A mesh that represents a torus. The level of detail/smoothness
 * can be specified in the constructor. */
class Torus : public Mesh
{

public:
	Torus(float innerRadius, float outerRadius, unsigned int numSides, unsigned int numRings);
	virtual ~Torus();

};

#endif
