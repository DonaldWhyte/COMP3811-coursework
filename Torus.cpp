#include "Torus.h"
#include <math.h>

Torus::Torus(float innerRadius, float outerRadius, unsigned int numSides, unsigned int numRings) : Mesh()
{
	// Increase sides and rings to generate an additional point
	numSides += 1;
	numRings += 1;

	VertexList generatedVertices;
	generatedVertices.reserve(numSides * numRings); // pre-allocate memory for vertices we know we'll need
	// How large the "step" between angles is when generating vertices
	float deltaPsi = 2.0f * PI / static_cast<float>(numRings - 1);
	float deltaPhi = -2.0f * PI / static_cast<float>(numSides - 1); // computed here so we don't need to re-compute them every iteration
	for (unsigned ring = 0; (ring < numRings); ring++)
	{
		float psi = deltaPsi * ring;
		float cosPsi = cos(psi);
		float sinPsi = sin(psi);
		for (unsigned side = 0; (side < numSides); side++)
		{
			float phi = deltaPhi * side;
			float cosPhi = cos(phi);
			float sinPhi = sin(phi);

			// Compute vertex position
			Vertex vert;
			vert.position = Vector3(
				cosPsi * (outerRadius + cosPhi * innerRadius),
				sinPsi * (outerRadius + cosPhi * innerRadius),
				sinPhi * innerRadius
			);
			vert.normal = Vector3(cosPsi * cosPhi, sinPsi * cosPhi, sinPhi);
			// NOTE: We're not computing texture coordinates for the torus - for this
			// particular application we don't care about texturing this object
			
			// Add computed vertex to list
			generatedVertices.push_back(vert);
		}
	}

	// Construct triangles to use generated vertices
	TriangleList generatedTriangles;
	for (unsigned side = 0; (side < numSides - 1); side++)
	{
		for (unsigned int ring = 0; (ring < numRings - 1); ring++)
		{
			int indexOffset = (ring * numSides + side);
			// Get vertex indices for a QUAD on the torus and split it into two triangles
			int v1 = indexOffset;
			int v2 = (indexOffset + 1);
			int v3 = (indexOffset + 1 * numSides + 1);
			int v4 = (indexOffset + 1 * numSides);
			generatedTriangles.push_back( Triangle(v1, v2, v3) );
			generatedTriangles.push_back( Triangle(v3, v4, v1) );
		}
	}
	
	setVertices(generatedVertices);
	setTriangles(generatedTriangles);
}

Torus::~Torus()
{
}
