#include "Drawable.h"

Drawable::Drawable() : method(RENDER_METHOD_TRIANGLES), pos(0.0f, 0.0f, 0.0f), rotationDeg(0.0f)
{
}

Drawable::~Drawable()
{
}

RenderMethod Drawable::renderMethod() const
{
        return method;
}

void Drawable::setRenderMethod(RenderMethod newMethod)
{
        method = newMethod;
}

float Drawable::x() const
{
        return pos.x;
}

float Drawable::y() const
{
        return pos.y;
}

float Drawable::z() const
{
	return pos.z;
}

const Vector3& Drawable::position() const
{
	return pos;
}

float Drawable::rotationDegrees() const
{
        return rotationDeg;
}

void Drawable::setX(float newX)
{
        pos.x = newX;
}

void Drawable::setY(float newY)
{
        pos.y = newY;
}

void Drawable::setZ(float newZ)
{
	pos.z = newZ;
}

void Drawable::setPosition(const Vector3& newPosition)
{
	pos = newPosition;
}

void Drawable::setRotationDegrees(float newDegrees)
{
        rotationDeg = newDegrees;
}
