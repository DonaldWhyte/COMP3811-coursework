#include <QGLWidget>
#include "GLPlatonicSolid.h"

GLPlatonicSolid::GLPlatonicSolid(PlatonicSolidType type, RenderMethod method) :
	method(method), solidType(type)
{
}

RenderMethod GLPlatonicSolid::renderMethod() const
{
	return method;
}

void GLPlatonicSolid::setRenderMethod(RenderMethod newMethod)
{
	method = newMethod;
}

PlatonicSolidType GLPlatonicSolid::type() const
{
	return solidType;
}

void GLPlatonicSolid::setType(PlatonicSolidType newType)
{
	solidType = newType;
}

void GLPlatonicSolid::render() const
{
}

