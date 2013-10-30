#include "SurfaceFactory.h"

Surface SurfaceFactory::createCylinder(float height, float radius, int numSegments)
{
	VertexList generatedVertices;
	TriangleList generatedTriangles;
	return Surface(generatedVertices, generatedTriangles);
}

Surface	SurfaceFactory::createCone(float height, float radius, int numSegments)
{
	VertexList generatedVertices;
	TriangleList generatedTriangles;
	return Surface(generatedVertices, generatedTriangles);
}

