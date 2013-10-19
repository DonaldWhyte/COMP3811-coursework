#include "Sphere.h"
#include <math.h>

Sphere::Sphere(float radius, int numRings, int numQuadsPerRing) : Mesh()
{
	// Construct a sphere using the given arguments
	VertexList generatedVertices;
	TriangleList generatedTriangles;
	unsigned int vertexCounter = 0;
	
	for (unsigned int ring = 0; (ring < numRings); ring++)
	{
		// Per-ring parameters
		float phi = -(PI / 2.0f) + (ring * (PI/ numRings));
		float nextPhi = -(PI / 2.0f) + ((ring + 1.0f) * (PI / numRings));
		float cosPhi = cos(phi);
		float sinPhi = sin(phi);
		float cosNextPhi = cos(nextPhi);
		float sinNextPhi = sin(nextPhi);
		for (unsigned int quad = 0; (quad < numQuadsPerRing); quad++)
		{
			// Compute parameters for computing vertices
			float theta = quad * ((2.0f * PI) / numQuadsPerRing);
			float nextTheta = (quad + 1.0f) * ((2.0f * PI) / numQuadsPerRing);
			float cosTheta = cos(theta);
			float sinTheta = sin(theta);
			float cosNextTheta = cos(nextTheta);
			float sinNextTheta = sin(nextTheta);
			// Compute vertex positions and normals
			Vertex v1, v2, v3, v4;
			// phi_i, theta_j
			v1.position = Vector3(radius * cosPhi * cosTheta, radius * cosPhi * sinTheta, radius * sinPhi);
			v1.normal = v1.position;
			// phi_i, theta_j+1
			v2.position = Vector3(radius * cosPhi * cosNextTheta, radius * cosPhi * sinNextTheta, radius * sinPhi);
			v2.normal = v2.position;
			// phi_i+1, theta_j+1
			v3.position = Vector3(radius * cosNextPhi * cosNextTheta, radius * cosNextPhi * sinNextTheta, radius * sinNextPhi);
			v3.normal = v3.position;
			// phi_i+1, theta_j
			v4.position = Vector3(radius * cosNextPhi * cosTheta, radius * cosNextPhi * sinTheta, radius * sinNextPhi);
			v4.normal = v4.position;
			generatedVertices.push_back(v1); generatedVertices.push_back(v2);
			generatedVertices.push_back(v3); generatedVertices.push_back(v4);

			// Create two triangles to render the quad
			generatedTriangles.push_back( Triangle(vertexCounter, vertexCounter+1, vertexCounter+2) );
			generatedTriangles.push_back( Triangle(vertexCounter+2, vertexCounter, vertexCounter+3) );
			vertexCounter += 4;
		}
	}
	
	setVertices(generatedVertices);
	setTriangles(generatedTriangles);
}

Sphere::~Sphere()
{
}
