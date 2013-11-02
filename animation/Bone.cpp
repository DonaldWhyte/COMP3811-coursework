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
    const KeyFrame& lastKeyFrame = keyframes[keyframes.size() - 1];
    totalFrames = lastKeyFrame.frameNumber;
}

Bone::Bone(Surface* surface, const Vector3& boneOrigin, const Vector3& boneRotation) :
	boneSurface(surface), currentFrame(0), totalFrames(1)
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
    // Loop back to beginning of animation if the end of it has been reached
    if (onLastFrame())
        currentFrame = 1;
    else
        currentFrame += 1;
}

void Bone::render()
{
	glPushMatrix();
    // Apply bone transformations using the current key frame's progress
    Vector3 interpolatedPosition = interpolatePositionKeyframes();
    Vector3 interpolatedRotation = interpolateRotationKeyframes();
	glTranslatef(interpolatedPosition.x, interpolatedPosition.y, interpolatedPosition.z);
	glRotatef(interpolatedRotation.x, 1.0f, 0.0f, 0.0f);	
	glRotatef(interpolatedRotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(interpolatedRotation.z, 0.0f, 0.0f, 1.0f);	
	// Render all of this bone's children
	for (BoneList::iterator it = childBones.begin(); (it != childBones.end()); it++)
		(*it)->render();
	// Render current bone itself
	if (boneSurface)
		boneSurface->render();

	glPopMatrix();
}

int Bone::currentKeyFrameIndex() const
{
    // Search through keyframes and return index of keyframe
    // BEFORE the keyframe which has not occurred yet
    for (int i = 1; (i < keyframes.size()); i++)
        if (currentFrame <= keyframes[i].frameNumber)
            return i - 1;
    // If control reaches this point, the current frame
    // has exceeded all keyframes, so just return the last one
    return (keyframes.size() - 1);
}

bool Bone::onLastFrame() const
{
    return (currentFrame == totalFrames);
}

const KeyFrame& Bone::currentKeyFrame() const
{
    return keyframes[currentKeyFrameIndex()];
}

const KeyFrame& Bone::nextKeyFrame() const
{
    int currentIndex = currentKeyFrameIndex();
    // If current keyframe is last key frame in animation,
    // loop back to the first key frame
    if (currentIndex == (keyframes.size() - 1))
        return keyframes[0];
    else
        return keyframes[currentIndex + 1];
}

float Bone::currentFrameProgress()
{
    // If the current key frame is the last one, then we
    // consider frame progress being 1
    if (currentKeyFrameIndex() == (keyframes.size() - 1))
    {
        return 0.0f;
    }
    else
    {
        int currentKeyframeNo = currentKeyFrame().frameNumber;    
        int nextKeyframeNo = nextKeyFrame().frameNumber;
        int frameDifference = (nextKeyframeNo - currentKeyframeNo);
        int intermediateFrameNo = std::max(0, (currentFrame - currentKeyframeNo));
        return (static_cast<float>(intermediateFrameNo) / static_cast<float>(frameDifference));
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
    return currentPos.lerp(nextPos, currentFrameProgress());
}

Vector3 Bone::interpolateRotationKeyframes()
{
    const KeyFrame& current = currentKeyFrame();
    const Vector3& currentRot = current.rotation;
    if (current.frameNumber == (keyframes.size() - 1))
        return currentRot;
    const Vector3& nextRot = nextKeyFrame().rotation;
    // Interpolate between the two key frames
    return currentRot.lerp(nextRot, currentFrameProgress());
}
