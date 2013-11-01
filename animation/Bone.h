#ifndef ANIMATION_BONE_H
#define ANIMATION_BONE_H

#include <vector>
#include "../surfaces/Surface.h"
#include "../util/Vector3.h"

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
    Vector3 interpolatePositionKeyframes();
    Vector3 interpolateRotationKeyframes();

	BoneList childBones;
	Surface* boneSurface;
	
	KeyFrameList keyframes;	
	int currentKeyframe;
	float currentFrameProgress; // (0 = start of keyframe, 1 = end of keyframe)

};

#endif
