#include "Animator.h"

Animator::Animator(int animationLength, Bone* rootBone) :
    animationLength(animationLength), rootBone(rootBone),
    currentFrameNo(0), paused(false)
{
}

bool Animator::isPaused() const
{
    return paused;
}

void Animator::setPause(bool paused)
{
    this->paused = paused;
}

void Animator::togglePause()
{
    paused = !paused;
}

int Animator::currentFrame() const
{
    return currentFrameNo;
}

void Animator::setCurrentFrame(int newCurrentFrame)
{
    currentFrameNo = newCurrentFrame;
    updateBoneHierarchy();
}

int Animator::totalFrames() const
{
    return animationLength;
}

void Animator::update()
{
    // Don't do anything if the animation is paused
    if (isPaused()) return;
    // Loop back to beginning of animation if the end of it has been reached
    if (onLastFrame())
        currentFrameNo = 1;
    else
        currentFrameNo += 1;
        
    updateBoneHierarchy();        
}

bool Animator::onLastFrame() const
{
    return (currentFrameNo == animationLength);
}

void Animator::updateBoneHierarchy()
{
    // Pass current frame number to the bone hierarchy
    // and update each bone's animation
    rootBone->update(currentFrameNo);
}
