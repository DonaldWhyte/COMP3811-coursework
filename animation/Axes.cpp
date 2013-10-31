#include "Axes.h"
#include "../surfaces/SurfaceFactory.h"

Bone* Axes::createXYZAxes(float axisLength, float endpointLength)
{
    // Generate required surfaces
	SurfaceFactory surfaceFactory;
	Surface* cylinder = surfaceFactory.createCylinder(axisLength, 0.05f, 32);
	Surface* cone = surfaceFactory.createCone(endpointLength, 0.05f, 32);
	// TODO: cleanup surfaces!
	
	Bone* rootBone = new Bone(NULL);
	Bone* xAxis = new Bone(cylinder, Vector3(0, 0, 0), Vector3(0, 90, 0));
	Bone* yAxis = new Bone(cylinder, Vector3(0, 0, 0), Vector3(90, 0, 0));
	Bone* zAxis = new Bone(cylinder, Vector3(0, 0, 0), Vector3(0, 0, 0));
	rootBone->addChild(xAxis); rootBone->addChild(yAxis); rootBone->addChild(zAxis);
	xAxis->addChild( new Bone(cone, Vector3(0, 0, 3.75f + 0.25f), Vector3(0, 0, 0)) );
	yAxis->addChild( new Bone(cone, Vector3(0, 0, 3.75f + 0.25f), Vector3(0, 0, 0)) );
	zAxis->addChild( new Bone(cone, Vector3(0, 0, 3.75f + 0.25f), Vector3(0, 0, 0)) );		
	xAxis->addChild( new Bone(cone, Vector3(0, 0, -3.75f - 0.25f), Vector3(0, 180, 0)) );
	yAxis->addChild( new Bone(cone, Vector3(0, 0, -3.75f - 0.25f), Vector3(0, 180, 0)) );
	zAxis->addChild( new Bone(cone, Vector3(0, 0, -3.75f - 0.25f), Vector3(0, 180, 0)) );	
	// NOTE: Don't need to worry about cleaning up bones.
	// This is handled by the root bone's destructor
	
	return rootBone;
}
