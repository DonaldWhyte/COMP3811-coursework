#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "Bone.h"

/* Used to control the animation of bones. */
class Animator
{

public:
    Animator(int animationLength, Bone* rootBone); 
    
    bool isPaused() const;
    void setPause(bool paused);
    void togglePause();
    
    int currentFrame() const;
    void setCurrentFrame(int newCurrentFrame);
    
    int totalFrames() const;
    
    void update();
    
private:
    bool onLastFrame() const;
    void updateBoneHierarchy();

    int animationLength; // in frames
    Bone* rootBone;
    int currentFrameNo;
    bool paused;
    
};

#endif
