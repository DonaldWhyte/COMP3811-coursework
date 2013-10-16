#include <QGLWidget>
#include "GLPlatonicSolid.h"
#include "Matrix44.h"

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
	// Clear existing transformations
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Construct transformation matrix manually
	Matrix44 transformation = Matrix44::scale(SCALING_FACTOR, SCALING_FACTOR, SCALING_FACTOR);
	transformation = transformation * Matrix44::translation(pos.x, pos.y, pos.z);
	transformation = transformation * Matrix44::zRotation(rotationDeg) * Matrix44::yRotation(rotationDeg);
	// Compute transformed vertices
	Vector3List vertices = getVertices();
	for (int i = 0; (i < vertices.size()); i++)
		vertices[i] = transformation * vertices[i];

	switch (method)
	{
	case RENDER_METHOD_POINTS:
		renderAsPoints(vertices);
		break;
	case RENDER_METHOD_LINES:
		renderAsLines(vertices, getLines());
		break;
	case RENDER_METHOD_TRIANGLES:
		renderAsTriangles(vertices, getTriangles());
		break;
	}

	glPopMatrix();
}

void GLPlatonicSolid::renderAsPoints(const Vector3List& vertices)
{
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (Vector3List::const_iterator it = vertices.begin(); (it != vertices.end()); it++)
	{
		glVertex3f(it->x, it->y, it->z);
	}
	glEnd();
}

void GLPlatonicSolid::renderAsLines(const Vector3List& vertices, const LineList& lines)
{
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

void GLPlatonicSolid::renderAsTriangles(const Vector3List& vertices, const TriangleList& triangles)
{
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
