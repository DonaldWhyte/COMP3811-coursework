#include <QGLWidget>
#include "GLPlatonicSolid.h"

static const float TRIANGLE_COLORS[2][3] = {
	{ 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f}
};

GLPlatonicSolid::GLPlatonicSolid() : colourTriangles(false)
{
}

const bool GLPlatonicSolid::trianglesColoured() const
{
	return colourTriangles;
}

void GLPlatonicSolid::setColourTriangles(bool willColourTriangles)
{
	colourTriangles = willColourTriangles;
}

void GLPlatonicSolid::render()
{
	// Apply standard drawable transformations
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(rotationDeg, 0.0f, 1.0f, 0.0f);
	glScalef(SCALING_FACTOR, SCALING_FACTOR, SCALING_FACTOR);

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
	glColor3f(1.0f, 1.0f, 1.0f);
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
	glColor3f(1.0f, 1.0f, 1.0f);
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
	const TriangleList& triangles = getTriangles();

	// Set solid colour if triangles are NOT being individually coloured
	if (!colourTriangles)
	{
		const float* solidCol = TRIANGLE_COLORS[0];
		glColor3f(solidCol[0], solidCol[1], solidCol[2]);
	}

	glBegin(GL_TRIANGLES);
	for (int i = 0; (i < triangles.size()); i++)
	{
		// Assign colour to the triangle if appropriate flag has been set
		if (colourTriangles)
		{
			const float* triCol = TRIANGLE_COLORS[i % 2];
			glColor3f(triCol[0], triCol[1], triCol[2]);
		}
		// Specify the triangle itself
		const Triangle& tri = triangles[i];
		const Vector3& v1 = vertices[tri.v1];
		const Vector3& v2 = vertices[tri.v2];
		const Vector3& v3 = vertices[tri.v3];
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
	}
	glEnd();
}
