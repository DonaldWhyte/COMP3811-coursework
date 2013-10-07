#ifndef GL_TETRA_H
#define GL_TETRA_H

#include "Drawable.h"
#include "Geometry.h"

enum RenderMethod
{
	RENDER_METHOD_POINTS = 0,
	RENDER_METHOD_LINES,
	RENDER_METHOD_TRIANGLES
};

class GLPlatonicSolid : public Drawable
{

public:
	GLPlatonicSolid(RenderMethod method = RENDER_METHOD_TRIANGLES);

	RenderMethod renderMethod() const;
	void setRenderMethod(RenderMethod newMethod);

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

	RenderMethod method;

};

#endif
