#ifndef GL_CONE_H
#define GL_CONE_H

#include "Mesh.h"

/* A mesh that represents a cone. The level of detail/smoothness
 * can be specified in the constructor. */
class Cone : public Mesh
{

public:
	Cone(float height, float radius, int numSegments);
	virtual ~Cone();
	
	TexCoord computeTexCoord(float angle, float currentHeight, float totalHeight);

};

#endif
