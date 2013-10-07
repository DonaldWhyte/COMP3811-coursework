#include <QGLWidget>
#include "GLPlatonicSolid.h"

GLPlatonicSolid::GLPlatonicSolid(RenderMethod method) : method(method)
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

void GLPlatonicSolid::render()
{
	// Apply standard drawable transformations
	glPushMatrix();
	glLoadIdentity();

	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(rotationDeg, 1.0f, 1.0f, 1.0f);

	switch (method)
	{
	case RENDER_METHOD_POINTS:
		renderAsPoints();
		break;
	case RENDER_METHOD_LINES:
		renderAsLines();
		break;
	case RENDER_METHOD_TRIANGLES:
		renderAsTriangles();
		break;
	}

	glPopMatrix();
}

void GLPlatonicSolid::renderAsPoints()
{
	const Vector3List& vertices = getVertices();

	glBegin(GL_POINTS);
	for (Vector3List::const_iterator it = vertices.begin(); (it != vertices.end()); it++)
	{
		glVertex3f(it->x, it->y, it->z);
	}
	glEnd();
}

void GLPlatonicSolid::renderAsLines()
{
	const Vector3List& vertices = getVertices();
	const LineList& lines = getLines();

	glBegin(GL_LINES);
	for (LineList::const_iterator it = lines.begin(); (it != lines.end()); it++)
	{
		const Vector3& v1 = vertices[it->v1];
		const Vector3& v2 = vertices[it->v2];
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
	}
	glEnd();
}

void GLPlatonicSolid::renderAsTriangles()
{
	const Vector3List& vertices = getVertices();
	const TriangleList& lines = getTriangles();

	glBegin(GL_TRIANGLES);
	for (TriangleList::const_iterator it = lines.begin(); (it != lines.end()); it++)
	{
		const Vector3& v1 = vertices[it->v1];
		const Vector3& v2 = vertices[it->v2];
		const Vector3& v3 = vertices[it->v3];
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
	}
}
