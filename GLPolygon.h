#ifndef GL_POLYGON_H
#define GL_POLYGON_H

#include "Drawable.h"

/* Used to represent and draw a polygon with an arbitrary 
 * number of points. Polygons represented by this class
 * have points evently spaced away from a central point,
 * with each angles between them. */
class GLPolygon : public Drawable
{

public:
	GLPolygon(int vertices = DEFAULT_NUM_VERTICES);

	/* Use to get/set the number of vertices the polygon has. */
	int numVertices() const;
	void setNumVertices(int newNumVertices);

	/* Draws polygon on screen. */
	void render();

private:
	/* If the number of vertices is not specified in the polygon's
 	 * constructor, this value is used. */
	static const int DEFAULT_NUM_VERTICES = 3;

	int nVertices;

};

#endif
