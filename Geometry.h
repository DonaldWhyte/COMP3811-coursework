#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

/* Basic geoemtrical structures are all contained iwithin this
 * file for convenience. */

struct Line
{
	int v1;
	int v2;

	Line(int v1, int v2) : v1(v1), v2(v2) { }
};

struct Triangle
{
	int v1;
	int v2;
	int v3;

	Triangle(int v1, int v2, int v3) : v1(v1), v2(v2), v3(v3) { }
};

typedef std::vector<Line> LineList;
typedef std::vector<Triangle> TriangleList;

extern const double PI;

float degreesToRadians(float degrees);

#endif
