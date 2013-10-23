#ifndef GL_CYLINDER_H
#define GL_CYLINDER_H

#include "Mesh.h"

/* A mesh that represents a sphere. The level of detail/smoothness
 * can be specified in the constructor. */
class Cylinder : public Mesh
{

public:
	Cylinder(float height, float radius, int numSegments);
	virtual ~Cylinder();
	
	TexCoord computeTexCoord(const Vector3& positionOnCylinder);

};

#endif
