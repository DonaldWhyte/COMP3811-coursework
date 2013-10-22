#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include "Vector3.h"

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

/* Simple structure used for texture coordinates. */
struct TexCoord
{
	float s, t;
	TexCoord() : s(0.0f), t(0.0f) { }
	TexCoord(float s, float t) : s(s), t(t) { }
};

/* Generic structure for storing all of a vertices properties. */
struct Vertex
{
	Vector3 position;
	Vector3 normal;
	TexCoord texCoord;
};

typedef std::vector<Line> LineList;
typedef std::vector<Triangle> TriangleList;
typedef std::vector<Vertex> VertexList;

extern const double PI;

float degreesToRadians(float degrees);

#endif
