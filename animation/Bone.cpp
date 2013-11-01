#include "Bone.h"
#include <QGLWidget> /// for OpenGL functions
#include <algorithm>
#include "../util/Matrix44.h"

KeyFrame::KeyFrame(int frameNumber, const Vector3& position, const Vector3& rotation) :
    frameNumber(frameNumber), position(position), rotation(rotation)
{
}

Bone::Bone(Surface* surface, const KeyFrameList& keyframes) :
	 boneSurface(surface), keyframes(keyframes), currentKeyframe(0), currentFrameProgress(0.0f)
{
}

Bone::Bone(Surface* surface, const Vector3& boneOrigin, const Vector3& boneRotation) :
	boneSurface(surface), currentKeyframe(0), currentFrameProgress(0.0f)
{
	// Construct initial keyframe to work with animation
	keyframes.push_back( KeyFrame(0, boneOrigin, boneRotation) );
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

void Bone::update()
{
    // TODO
}

void Bone::render()
{
	glPushMatrix();
    // Apply bone transformations for the current ke
    Vector3 interpolatedPosition = interpolatePositionKeyframes();
    Vector3 interpolatedRotation = interpolateRotationKeyframes();
	glTranslatef(interpolatedPosition.x, interpolatedPosition.y, interpolatedPosition.z);
	glRotatef(interpolatedRotation.x, 1.0f, 0.0f, 0.0f);	
	glRotatef(interpolatedRotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(interpolatedRotation.z, 0.0f, 0.0f, 1.0f);	
	// Render all of this bone's childBones
	for (BoneList::iterator it = childBones.begin(); (it != childBones.end()); it++)
		(*it)->render();
	// Render current bone itself
	if (boneSurface)
		boneSurface->render();

	glPopMatrix();
}

Vector3 Bone::interpolatePositionKeyframes()
{
    // TODO
    return keyframes[currentKeyframe].position;
}

Vector3 Bone::interpolateRotationKeyframes()
{
    // TODO
    return keyframes[currentKeyframe].rotation;
}
