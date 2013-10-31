#include "Bone.h"
#include <QGLWidget> /// for OpenGL functions
#include <algorithm>
#include "../util/Matrix44.h"

Bone::Bone(Surface* surface, const Vector3& boneOrigin, const Vector3& boneRotation) :
	boneSurface(surface), boneOrigin(boneOrigin), boneRotation(boneRotation)
{
}

Bone::~Bone()
{
	// Make sure to delete all children bones
	for (BoneList::iterator it = childBones.begin(); (it != childBones.end()); it++)
		delete (*it);
}

Surface* Bone::surface() const
{
	return boneSurface;
}

void Bone::setSurface(Surface* newSurface)
{
	boneSurface = newSurface;
}

Vector3 Bone::origin() const
{
	return boneOrigin;
}

void Bone::setOrigin(const Vector3& newOrigin)
{
	boneOrigin = newOrigin;
}

Vector3 Bone::rotation() const
{
	return boneRotation;
}

void Bone::setRotation(const Vector3& newRotation)
{
	boneRotation = newRotation;
}

void Bone::addChild(Bone* bone)
{
	childBones.push_back(bone);
}

void Bone::removeChild(Bone* bone)
{
	// Remove all elements that point to the same bone
	childBones.erase(std::remove(childBones.begin(), childBones.end(), bone), childBones.end());
}

const Bone::BoneList& Bone::children() const {
	return childBones;
}

#include <iostream>
void Bone::render()
{
	glPushMatrix();
    // Apply bone transformations
	glTranslatef(boneOrigin.x, boneOrigin.y, boneOrigin.z);
	glRotatef(boneRotation.x, 1.0f, 0.0f, 0.0f);	
	glRotatef(boneRotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(boneRotation.z, 0.0f, 0.0f, 1.0f);	
	// Render all of this bone's childBones
	for (BoneList::iterator it = childBones.begin(); (it != childBones.end()); it++)
		(*it)->render();
	// Render current bone itself
	if (boneSurface)
		boneSurface->render();

	glPopMatrix();
}
