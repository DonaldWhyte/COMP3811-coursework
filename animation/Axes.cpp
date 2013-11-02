#include "Axes.h"
#include "../surfaces/SurfaceFactory.h"

Bone* Axes::createXYZAxes(float axisLength, float endpointLength)
{
    // Generate required surfaces
	SurfaceFactory surfaceFactory;
	Surface* xSurface = surfaceFactory.createCylinder(axisLength, 0.05f, 32);
	Surface* xSurfaceTip = surfaceFactory.createCone(endpointLength, 0.2f, 32);
	xSurface->setColour(Vector3(1.0f, 0.0f, 0.0f));
	xSurfaceTip->setColour(Vector3(1.0f, 0.0f, 0.0f));
	Surface* ySurface = surfaceFactory.createCylinder(axisLength, 0.05f, 32);
	Surface* ySurfaceTip = surfaceFactory.createCone(endpointLength, 0.2f, 32);
	ySurface->setColour(Vector3(0.0f, 1.0f, 0.0f));
	ySurfaceTip->setColour(Vector3(0.0f, 1.0f, 0.0f));	
	Surface* zSurface = surfaceFactory.createCylinder(axisLength, 0.05f, 32);
	Surface* zSurfaceTip = surfaceFactory.createCone(endpointLength, 0.2f, 32);
	zSurface->setColour(Vector3(0.0f, 0.0f, 1.0f));
	zSurfaceTip->setColour(Vector3(0.0f, 0.0f, 1.0f));	
	// TODO: cleanup surfaces!
	
	Bone* rootBone = new Bone(NULL);
	Bone* xAxis = new Bone(xSurface, Vector3(0, 0, 0), Vector3(0, 90, 0));
	Bone* yAxis = new Bone(ySurface, Vector3(0, 0, 0), Vector3(90, 0, 0));
	Bone* zAxis = new Bone(zSurface, Vector3(0, 0, 0), Vector3(0, 0, 0));
	rootBone->addChild(xAxis); rootBone->addChild(yAxis); rootBone->addChild(zAxis);
	xAxis->addChild( new Bone(xSurfaceTip, Vector3(0, 0, (axisLength / 2) + (endpointLength / 2)), Vector3(0, 0, 0)) );
	yAxis->addChild( new Bone(ySurfaceTip, Vector3(0, 0, (axisLength / 2) + (endpointLength / 2)), Vector3(0, 0, 0)) );
	zAxis->addChild( new Bone(zSurfaceTip, Vector3(0, 0, (axisLength / 2) + (endpointLength / 2)), Vector3(0, 0, 0)) );		
	xAxis->addChild( new Bone(xSurfaceTip, Vector3(0, 0, -(axisLength / 2) - (endpointLength / 2)), Vector3(0, 180, 0)) );
	yAxis->addChild( new Bone(ySurfaceTip, Vector3(0, 0, -(axisLength / 2) - (endpointLength / 2)), Vector3(0, 180, 0)) );
	zAxis->addChild( new Bone(zSurfaceTip, Vector3(0, 0, -(axisLength / 2) - (endpointLength / 2)), Vector3(0, 180, 0)) );	
	// NOTE: Don't need to worry about cleaning up bones.
	// This is handled by the root bone's destructor
	
	return rootBone;
}
