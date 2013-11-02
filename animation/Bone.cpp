#include "Bone.h"
#include <QGLWidget> /// for OpenGL functions
#include <algorithm>
#include "../util/Matrix44.h"

KeyFrame::KeyFrame(int frameNumber, const Vector3& position, const Vector3& rotation) :
    frameNumber(frameNumber), position(position), rotation(rotation)
{
}

Bone::Bone(Surface* surface, const KeyFrameList& keyframes) :
	 boneSurface(surface), keyframes(keyframes), currentFrame(0)
{
}

Bone::Bone(Surface* surface, const Vector3& boneOrigin, const Vector3& boneRotation) :
	boneSurface(surface), currentFrame(0)
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
    // Increase frame count
    currentFrame += 1;
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

int Bone::currentKeyFrameIndex() const
{
    // Search through keyframes and return index of first
    // keyframe whose frame number is GREATER THAN OR
    // EQUAL to the current frame
    for (int i = 0; (i < keyframes.size()); i++)
        if (currentFrame <= keyframes[i].frameNumber)
            return i;
}

const KeyFrame& Bone::currentKeyFrame() const
{
    return keyframes[currentKeyFrameIndex()];
}

const KeyFrame& Bone::nextKeyFrame() const
{
    int currentIndex = currentKeyFrameIndex();
    // If current keyftrame is not last key frame in animation
    if (currentIndex < (keyframes.size() - 1))
        return keyframes[currentIndex + 1];
    else
        return keyframes[currentIndex];
}

float Bone::currentFrameProgress()
{
    // If the current key frame is the last one, then the frame
    // progress is fixed at 0
    const KeyFrame& current = currentKeyFrame();
    int currentKeyframeNo = current.frameNumber;
    if (currentKeyframeNo == (keyframes.size() - 1))
    {
        return 0.0f;
    }
    else
    {
        int nextKeyframeNo = nextKeyFrame().frameNumber;
        int frameDifference = (nextKeyframeNo - currentKeyframeNo);
        int intermediateFrameNo = std::max(1, (currentFrame - currentKeyframeNo));
        return (frameDifference / intermediateFrameNo);    
    }
}

Vector3 Bone::interpolatePositionKeyframes()
{
    const KeyFrame& current = currentKeyFrame();
    const Vector3& currentPos = current.position;
    if (current.frameNumber == (keyframes.size() - 1))
        return currentPos;
    const Vector3& nextPos = nextKeyFrame().position;
    // Interpolate between the two key frames
    return interpolate(currentPos, nextPos, currentFrameProgress());
}

Vector3 Bone::interpolateRotationKeyframes()
{
    const KeyFrame& current = currentKeyFrame();
    const Vector3& currentRot = current.rotation;
    if (current.frameNumber == (keyframes.size() - 1))
        return currentRot;
    const Vector3& nextRot = nextKeyFrame().rotation;
    // Interpolate between the two key frames
    return interpolate(currentRot, nextRot, currentFrameProgress());
}

Vector3 Bone::interpolate(const Vector3& a, const Vector3& b, float t)
{
	return Vector3(t * a.x + (1 - t) * b.x,
		t * a.y + (1 - t) * b.y,
		t * a.z + (1 - t) * b.z);
}
