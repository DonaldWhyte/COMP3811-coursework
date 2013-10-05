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
        float rotationDegrees() const;
        /* Used to specify the position and orientation of object. */
	void setX(float newX);
	void setY(float newY);
	void setZ(float newZ);
        void setPosition(const Vector3& newPosition);
        void setRotationDegrees(float newDegrees);

protected:
        Vector3 pos;
        float rotationDeg;

};

#endif
