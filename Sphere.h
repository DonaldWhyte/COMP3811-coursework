#ifndef GL_SPHERE_H
#define GL_SPHERE_H

#include "Mesh.h"

/* A mesh that represents a sphere. The level of detail/smoothness
 * can be specified in the constructor. */
class Sphere : public Mesh
{

public:
	Sphere(float radius, int numRings, int numQuadsPerRing);
	virtual ~Sphere();
	
	TexCoord computeTexCoord(const Vector3& positionOnSphere);

	bool usingPerFaceNormals() const;
	void setPerFaceNormals(bool willUseNormals);

};

#endif
