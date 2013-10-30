#ifndef SKELETON_H
#define SKELETON_H

#include "../Drawable.h"
#include "Bone.h"

class Skeleton : public Drawable
{

public:
	Skeleton(Bone* rootBone);

	void render();

private:
	Bone* rootBone;

};

#endif
