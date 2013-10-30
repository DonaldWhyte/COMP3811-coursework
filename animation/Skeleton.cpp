#include "Skeleton.h"
#include <QGLWidget>

Skeleton::Skeleton(Bone* rootBone) : rootBone(rootBone)
{
}

void Skeleton::render()
{
	// Perform root transformations for skeleton
	glPushMatrix();
	glRotatef(rot.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rot.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rot.z, 0.0f, 0.0f, 1.0f);
	glTranslatef(pos.x, pos.y, pos.z);
	rootBone->render();
	glPopMatrix();
}
