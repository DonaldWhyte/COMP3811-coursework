#ifndef GL_TETRA_H
#define GL_TETRA_H

#include "Drawable.h"
#include "Geometry.h"

class GLPlatonicSolid : public Drawable
{

public:
	/* Draw platonic solid on screen. */
	void render();

	/* These define the actual polyhedra rendered. */
	virtual const Vector3List& getVertices() const = 0;
	virtual const LineList& getLines() const = 0;
	virtual const TriangleList& getTriangles() const = 0;

private:
	static const float SCALING_FACTOR = 0.5f;

	void renderAsPoints();
	void renderAsLines();
	void renderAsTriangles();

};

#endif
