#ifndef GL_POLYGON_H
#define GL_POLYGON_H

/* Used to represent and draw a polygon with an arbitrary 
 * number of points. Polygons represented by this class
 * have points evently spaced away from a central point,
 * with each angles between them. */
class GLPolygon
{

public:
	GLPolygon(int vertices = DEFAULT_NUM_VERTICES, float x = 0.0f, float y = 0.0, float rotation = 0.0f);

	/* Used to retrieve position and orientation of polygon. */
	float x() const;
	float y() const;
	float rotationDegrees() const;
	/* Used to specify the position and orientation of polygno. */
	void setX(float x);
	void setY(float y);
	void setRotationDegrees(float newDegrees);

	/* Use to get/set the number of vertices the polygon has. */
	int numVertices() const;
	void setNumVertices(int newNumVertices);

	/* Draws polygon on screen. */
	void render() const;

private:
	/* If the number of vertices is not specified in the polygon's
 	 * constructor, this value is used. */
	static const int DEFAULT_NUM_VERTICES = 3;

	int nVertices;
	float posX, posY;
	float rotationDeg;

};

#endif
