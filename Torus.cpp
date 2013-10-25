#include "Torus.h"
#include <math.h>

Torus::Torus(float innerRadius, float outerRadius, unsigned int numSides, unsigned int numRings) : Mesh()
{
	// Increase sides and rings to generate an additional point
	numSides += 1;
	numRings += 1;

	// Generate vertices, creating enough vertices for the torus at the start
	unsigned int vertexCount = numSides * numRings;
	VertexList generatedVertices(vertexCount);
	float deltaPsi = 2.0f * PI / static_cast<float>(numRings - 1);
	float deltaPhi = -2.0f * PI / static_cast<float>(numSides - 1);
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
			vert.position = Vector3(cosPsi * (outerRadius + cosPhi * innerRadius), // X
				sinPsi * (outerRadius + cosPhi * innerRadius), // Y
				sinPhi * innerRadius // Z
			);
			vert.normal = Vector3(cosPsi * cosPhi, // X
				sinPsi * cosPhi, // Y
				sinPhi // Z
			);
			// Add computed vertex
			int offset = (ring * numSides + side);
			generatedVertices[offset] = vert;
		}
	}

	// Construct triangles to use generated vertices
	TriangleList generatedTriangles;
	for (unsigned side = 0; (side < numSides - 1); side++)
	{
		for (unsigned int ring = 0; (ring < numRings - 1); ring++)
		{
			int offset = (ring * numSides + side);
			int v1 = offset;
			int v2 = (offset + 1);
			int v3 = (offset + 1 * numSides + 1);
			int v4 = (offset + 1 * numSides);
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

TexCoord Torus::computeTexCoord(const Vector3& posOnTorus)
{
	float s = 0.5f + (atan2(posOnTorus.z, posOnTorus.x) / (2.0f * PI));
	float t = 0.5f - (asin(posOnTorus.y) / PI);
	return TexCoord(s, t); 
}
