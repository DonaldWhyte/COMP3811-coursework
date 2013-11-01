#ifndef SKELETON_H
#define SKELETON_H

#include "../Drawable.h"
#include "Bone.h"

class Skeleton : public Drawable
{

public:
	Skeleton(Bone* rootBone);
	virtual ~Skeleton();

	void render();

protected:
	Bone* rootBone;

};

#endif
