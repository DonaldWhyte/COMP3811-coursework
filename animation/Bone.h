#ifndef ANIMATION_BONE_H
#define ANIMATION_BONE_H

#include <vector>
#include "../surfaces/Surface.h"
#include "../util/Vector3.h"

class Bone
{

public:
	typedef std::vector<Bone*> BoneList;

	Bone(Surface* surface,
		const Vector3& origin = Vector3(0, 0, 0),
		const Vector3& rotation = Vector3(0, 0, 0));
	virtual ~Bone();

	Surface* surface() const;
	void setSurface(Surface* newSurface);
	Vector3 origin() const;
	void setOrigin(const Vector3& newOrigin);
	Vector3 rotation() const;
	void setRotation(const Vector3& newRotation);

	void addChild(Bone* bone);
	void removeChild(Bone* bone);
	const BoneList& children() const;

	void render();

private:
	BoneList childBones;
	Surface* boneSurface;
	Vector3 boneOrigin;
	Vector3 boneRotation;

};

#endif
