#include <QGLWidget>
#include <QPoint>
#include <math.h>
#include <vector>
#include "GLPolygon.h"
#include "BoundingBox.h"
#include "Geometry.h"

static const float VERTEX_COLOURS[3][3] = {
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f }
};


GLPolygon::GLPolygon(int vertices) : nVertices(vertices)
{
}

void GLPolygon::setNumVertices(int newNumVertices)
{
	nVertices = newNumVertices;
}

int GLPolygon::numVertices() const
{
	return nVertices;
}

void GLPolygon::render()
{
	// Angle between two different vertices from central
	// point of the polygon
	float angleDelta = PI / nVertices * 2;
	// Add an extra vertex so triangle fan rendering works nicely
	int vertexCount = nVertices + 1;

	// Compute position of all vertices of polygon
	std::vector<QPointF> positions;
	positions.reserve(vertexCount);
	for (int i = 0; (i < vertexCount); i++)
	{
		// Radius of 0.75 used for bounding circle
		float x = 0.75 * sin(angleDelta * i);
		float y = 0.75 * cos(angleDelta * i);
		positions.push_back( QPointF(x, y) );
	}
	// Compute central point of polygon using its bounding box
	float minX = positions[0].x();
	float minY = positions[1].y();
	float maxX = minX;
	float maxY = minY;
	for (int i = 1; (i < positions.size()); i++)
	{
		if (positions[i].x() < minX)
			minX = positions[i].x();
		else if (positions[i].x() > maxX)
			maxX = positions[i].x();
		if (positions[i].y() < minY)
			minY = positions[i].y();
		else if (positions[i].y() > maxY)
			maxY = positions[i].y();
	}
	BoundingBox bbox = BoundingBox(positions);

	// Setup polygon transformations
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(pos.x,  pos.y, pos.z);
	glRotatef(rotationDeg, 0.0f, 0.0f, 1.0f);
	// Draw centre point then remaining vertices
	glBegin(GL_TRIANGLE_FAN);
		const float* centralColour = VERTEX_COLOURS[2];
		glColor3f(centralColour[0], centralColour[1], centralColour[2]);
		glVertex2f(bbox.centreX(), bbox.centreY());
		for (int i = 0; (i < vertexCount); i++)
		{
			// We loop through three hard-coded colours
			// to ensure each vertex can be identified visually
			int colIndex = i % 2;
			const float* colour = VERTEX_COLOURS[colIndex];
			float x = positions[i].x();
			float y = positions[i].y();
		
			glColor3f(colour[0], colour[1], colour[2]);
			glVertex2f(x, y);
		}
	glEnd();
	glPopMatrix();
}
