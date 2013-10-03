#include "BoundingBox.h"

BoundingBox::BoundingBox(const std::vector<QPointF>& points)
{
        minXVal = points[0].x();
        minYVal = points[1].y();
        maxXVal = minXVal;
        maxYVal = minYVal;
        for (int i = 1; (i < points.size()); i++)
        {
                if (points[i].x() < minXVal)
                        minXVal = points[i].x();
                else if (points[i].x() > maxXVal)
                        maxXVal = points[i].x();
                if (points[i].y() < minYVal)
                        minYVal = points[i].y();
                else if (points[i].y() > maxYVal)
                        maxYVal = points[i].y();
        }
        centreXVal = minXVal + ((maxXVal - minYVal) / 2.0f);
        centreYVal = minXVal + ((maxXVal - minYVal) / 2.0f);
}

float BoundingBox::minX() const { return minXVal; } 
float BoundingBox::minY() const { return minYVal; } 
float BoundingBox::maxX() const { return maxXVal; } 
float BoundingBox::maxY() const { return maxYVal; } 
float BoundingBox::centreX() const { return centreXVal; } 
float BoundingBox::centreY() const { return centreYVal; } 
