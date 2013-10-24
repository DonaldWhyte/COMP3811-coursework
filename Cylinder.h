#ifndef GL_CYLINDER_H
#define GL_CYLINDER_H

#include "Mesh.h"

/* A mesh that represents a cylinder. The level of detail/smoothness
 * can be specified in the constructor. */
class Cylinder : public Mesh
{

public:
	Cylinder(float height, float radius, int numSegments);
	virtual ~Cylinder();
	
	TexCoord computeTexCoord(float angle, float currentHeight, float totalHeight);

};

#endif
