#ifndef GL_TETRA_H
#define GL_TETRA_H

#include "Drawable.h"
#include "Geometry.h"

/* Determines the solid's triangles are coloured. */
enum TriangleColourMode
{
	TRIANGLE_COL_SAME = 0, // all same colour
	TRIANGLE_COL_ALTERNATE, // alternating block colours
	TRIANGLE_COL_INTERPOLATE // interpolate from one colour to another over all triangles
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
