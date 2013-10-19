#include "Sphere.h"

Sphere::Sphere(float radius, int numRings, int numQuadsPerRing) : Mesh()
{
	// Construct a sphere using the given arguments
	VertexList generatedVertices;
	
	// TODO
	
	// Assign these vertices to the mesh
	setVertices(generatedVertices);
}

Sphere::~Sphere()
{
}
