#include <QPointF>
#include <vector>

/* Represents box with bounds a number of points. */
class BoundingBox
{

public:
	/* Construct box that tightly bounds all of the given points. */
	BoundingBox(const std::vector<QPointF>& points);

	/* The lower and upper bounds of the box. */
	float minX() const;
	float minY() const;
	float maxX() const;
	float maxY() const;
	/* Central point of box. */
	float centreX() const;
	float centreY() const;

private:
	float minXVal, maxXVal;
	float minYVal, maxYVal;
	float centreXVal, centreYVal;

};
