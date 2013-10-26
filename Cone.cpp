#include "Cone.h"
#include <math.h>

Cone::Cone(float height, float radius, int numSegments) : Mesh()
{
	// Construct a cone using the given argument
	VertexList generatedVertices;
	TriangleList generatedTriangles;
	int vertexCounter = 0;
	// Generate top and bottom vertices
	float halfHeight  (height / 2.0f);
	Vertex topCentre;
	topCentre.position = Vector3(0.0f, 0.0f, halfHeight);
	topCentre.normal = topCentre.position.normalise();
	topCentre.texCoord = TexCoord(1.0f, 0.5f);
	generatedVertices.push_back(topCentre);
	Vertex bottomCentre;
	bottomCentre.position = Vector3(0.0f, 0.0f, -halfHeight);
	bottomCentre.normal = bottomCentre.position.normalise();
	bottomCentre.texCoord = TexCoord(0.5, 0.5f);
	generatedVertices.push_back(bottomCentre);
	vertexCounter += 2;
	// Generate the 'tower' part of the cone
	for (float i = 0.0f; (i < numSegments); i += 1.0f)
	{
		float angle = (PI * i * 2.0f) / numSegments;
		float nextAngle = (PI * (i + 1.0f) * 2.0f) / numSegments;
		float x1 = radius * sin(angle), y1 = radius * cos(angle);
		float x2 = radius * sin(nextAngle), y2 = radius * cos(nextAngle);
		// We compute these two vertices TWICE. This is because we want
		// different normals at the bottom of the cone
		Vertex v1, v2, bv1, bv2;
		v1.position = Vector3(x1, y1, -halfHeight);
		v2.position = Vector3(x2, y2, -halfHeight);
		v1.texCoord = computeTexCoord(angle, v1.position.z, height);
		v2.texCoord = computeTexCoord(nextAngle, v2.position.z, height);
		bv1 = v1;
		bv2 = v2;
		v1.normal = v1.position.normalise();
		v2.normal = v2.position.normalise();
		bv1.normal = bv2.normal = Vector3(0.0f, 0.0f, -1.0f);
		generatedVertices.push_back(v1);
		generatedVertices.push_back(v2);
		generatedVertices.push_back(bv1);
		generatedVertices.push_back(bv2);
	
		// Triangle for tower part
		generatedTriangles.push_back( Triangle(0, vertexCounter, vertexCounter + 1) );
		// Triangle for bottom section
		generatedTriangles.push_back( Triangle(1, vertexCounter + 3, vertexCounter + 2) );
		vertexCounter += 4;
	}

	setVertices(generatedVertices);
	setTriangles(generatedTriangles);
}

Cone::~Cone()
{
}

TexCoord Cone::computeTexCoord(float angle, float currentHeight, float totalHeight)
{
	return TexCoord((angle / (2.0f * PI)), // s
		(currentHeight + (totalHeight / 2.0f)) / totalHeight // t
	);
}
