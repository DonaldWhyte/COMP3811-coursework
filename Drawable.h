#ifndef ABSTRACT_DRAWABLE_H
#define ABSTRACT_DRAWABLE_H

#include "Vector3.h"

/* Abstract class for drawable objects in the scene. Contains properties
 * and behaviour common to many drawable objects. */
class Drawable
{

public:
	Drawable();
	virtual ~Drawable();

	/* Abstract method which subclasses should use to implement
 	 * actual rendering functionality. */
	virtual void render() = 0;

        /* Used to retrieve position and orientation of object. */
	float x() const;
	float y() const;
	float z() const;
        const Vector3& position() const;
        float xRotation() const;
	float yRotation() const;
	float zRotation() const;
	const Vector3& rotation() const;
        /* Used to specify the position and orientation of object. */
	void setX(float newX);
	void setY(float newY);
	void setZ(float newZ);
        void setPosition(const Vector3& newPosition);
	void setXRotation(float newXRot);
	void setYRotation(float newYRot);
	void setZRotation(float newZRot);
        void setRotation(const Vector3& newRotation);

protected:
        Vector3 pos;
	Vector3 rot; // rotation about 3 primary axes in degrees

};

#endif
