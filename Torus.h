#ifndef GL_TORUS_H
#define GL_TORUS_H

#include "Mesh.h"

/* A mesh that represents a torus. The level of detail/smoothness
 * can be specified in the constructor. */
class Torus : public Mesh
{

public:
	Torus(float radius, int numSegments, int numQuadsPerSegment);
	virtual ~Torus();
	
	TexCoord computeTexCoord(const Vector3& positionOnTorus);

};

#endif
