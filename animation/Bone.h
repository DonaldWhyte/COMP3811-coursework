#ifndef ANIMATION_BONE_H
#define ANIMATION_BONE_H

#include <vector>
#include "../surfaces/Surface.h"
#include "../util/Vector3.h"

/* Represents a single key frame of a bone in skeletal animation.
 * Contains the position and rotation of a bone at specific
 * frame. */
struct KeyFrame
{
    int frameNumber;
    Vector3 position;
    Vector3 rotation;
    
    KeyFrame(int frameNumber,
        const Vector3& position = Vector3(0, 0, 0),
		const Vector3& rotation = Vector3(0, 0, 0));
		
};

typedef std::vector<KeyFrame> KeyFrameList;

class Bone
{

public:
	typedef std::vector<Bone*> BoneList;

	Bone(Surface* surface, const KeyFrameList& keyframes);
	Bone(Surface* surface,
	    const Vector3& origin = Vector3(0, 0, 0),
	    const Vector3& rotation = Vector3(0, 0, 0));
	virtual ~Bone();

	Surface* surface() const;
	void setSurface(Surface* newSurface);
	
	void addChild(Bone* bone);
	void removeChild(Bone* bone);
	const BoneList& children() const;

    void update(); // updates bone animation
	void render();

private:
    /* Return INDEX to current keyframe of bone animation. */
    int currentKeyFrameIndex() const;    
    /* Return current keyframe of bone animation. */ 
    const KeyFrame& currentKeyFrame() const;
    /* Return next keyframe of bone animation. */
    const KeyFrame& nextKeyFrame() const;
	/* Return the progress between the current key frame
 	 * and the next as a float in the range of 0 to 1. */
	float currentFrameProgress();

	Vector3 interpolatePositionKeyframes();
	Vector3 interpolateRotationKeyframes();

	BoneList childBones;
	Surface* boneSurface;
	
	KeyFrameList keyframes;	
	int currentFrame; // what frame of the animation the bone is currently in

};

#endif
