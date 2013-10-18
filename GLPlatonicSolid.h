#ifndef GL_TETRA_H
#define GL_TETRA_H

#include "Drawable.h"
#include "Geometry.h"

enum TriangleColourMode
{
	TRIANGLE_COL_SAME = 0,
	TRIANGLE_COL_ALTERNATE,
	TRIANGLE_COL_INTERPOLATE
};

class GLPlatonicSolid : public Drawable
{

public:
	GLPlatonicSolid();

	TriangleColourMode colourMode() const;
	void setColourMode(TriangleColourMode newMode);

	/* Draw platonic solid on screen. */
	void render();

	/* These define the actual polyhedra rendered. */
	virtual const Vector3List& getVertices() const = 0;
	virtual const LineList& getLines() const = 0;
	virtual const TriangleList& getTriangles() const = 0;

private:
	void renderAsPoints(const Vector3List& vertices);
	void renderAsLines(const Vector3List& vertices, const LineList& lines);
	void renderAsTriangles(const Vector3List& vertices, const TriangleList& triangles);

	static const float SCALING_FACTOR = 0.5f;

	TriangleColourMode colMode;

};

#endif
