#ifndef ABSTRACT_DRAWABLE_H
#define ABSTRACT_DRAWABLE_H

#include "Vector3.h"

enum RenderMethod
{
	RENDER_METHOD_POINTS = 0,
	RENDER_METHOD_LINES,
	RENDER_METHOD_TRIANGLES
};

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

	/* Used to provide hints on how to render the object.
 	 * Note that these may not be used by particular objects. */
        RenderMethod renderMethod() const;
        void setRenderMethod(RenderMethod newMethod);
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
	RenderMethod method;
        Vector3 pos;
	Vector3 rot; // rotation about 3 primary axes in degrees

};

#endif
