#ifndef SURFACE_FACTORY_H
#define SURFACE_FACTORY_H

#include "../util/Vector3.h"
#include "../util/Geometry.h"
#include "Surface.h"

/* Factory class which can generate a variety of different surfaces. */
class SurfaceFactory
{

public:
	Surface* createCylinder(float height, float radius, int numSegments);
	Surface* createCone(float height, float radius, int numSegments);
	Surface* createBox(float width, float height, float length);
	Surface* createSphere(float radius, int numRings, int numQuadsPerRing);

private:
    TexCoord computeSphereTexCoord(const Vector3& posOnSphere);

};

#endif
