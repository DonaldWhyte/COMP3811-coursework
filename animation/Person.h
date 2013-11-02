#ifndef PERSON_BONES_H
#define PERSON_BONES_H

#include "Skeleton.h"
#include "../surfaces/SurfaceFactory.h"

class Person : public Skeleton
{

public:
    Person(SurfaceFactory* surfaceFactory);
    virtual ~Person();
    
    Bone* getRootBone();
    
private:
    // Bone generation methods
    Bone* createBones(SurfaceFactory* surfaceFactory);
    Bone* createLeg(SurfaceFactory* surfaceFactory, Vector3 rootPosition, Vector3 rootOrientation);
    Bone* createArm(SurfaceFactory* surfaceFactory, Vector3 rootPosition, Vector3 rootOrientation, bool reverseDirection);

    std::vector<Surface*> surfaces;

};

#endif
