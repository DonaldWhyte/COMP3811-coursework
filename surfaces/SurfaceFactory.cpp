#include "SurfaceFactory.h"
#include <math.h>

#include <iostream>

Surface SurfaceFactory::createCylinder(float height, float radius, int numSegments)
{
    // Construct a cylinder using the given arguments
	VertexList generatedVertices;
	TriangleList generatedTriangles;
	int vertexCounter = 0;
	// Generate the 'tower' part of the cylinder
	for (float i = 0.0f; (i < numSegments); i += 1.0f)
	{
		float angle = (PI * i * 2.0f) / numSegments;
		float nextAngle = (PI * (i + 1.0f) * 2.0f) / numSegments;
		float x1 = radius * sin(angle), y1 = radius * cos(angle);
		float x2 = radius * sin(nextAngle), y2 = radius * cos(nextAngle);
		
		Vertex v1, v2, v3, v4;
		v1.position = Vector3(x1, y1, -(height / 2.0f));
		v1.normal = Vector3(x1, y1, 0.0f).normalise();
		v2.position = Vector3(x2, y2, height / 2.0f);
		v2.normal = Vector3(x2, y2, 0.0f).normalise();
		v3.position = Vector3(x1, y1, height / 2.0f);
		v3.normal = Vector3(x1, y1, 0.0f).normalise();
		v4.position = Vector3(x2, y2, -(height / 2.0f));
		v4.normal = Vector3(x2, y2, 0.0f).normalise();

		generatedVertices.push_back(v1); generatedVertices.push_back(v2);
		generatedVertices.push_back(v3); generatedVertices.push_back(v4);
	
		generatedTriangles.push_back( Triangle(vertexCounter, vertexCounter + 1, vertexCounter + 2) );
		generatedTriangles.push_back( Triangle(vertexCounter + 3, vertexCounter + 1, vertexCounter) );
		vertexCounter += 4;
	}
	// Generate top and bottom sections
	Vertex topCentre, bottomCentre;
	topCentre.position = Vector3(0.0f, 0.0f, height / 2.0f);
	topCentre.normal = Vector3(0.0f, 0.0f, 1.0f);
	bottomCentre.position = Vector3(0.0f, 0.0f, -(height / 2.0f));
	bottomCentre.normal = Vector3(0.0f, 0.0f, -1.0f);
	generatedVertices.push_back(topCentre);
	generatedVertices.push_back(bottomCentre);
	// Store indices to these two vertices for convenient triangle generation later
	unsigned int topIndex = vertexCounter;
	unsigned int bottomIndex = vertexCounter + 1;
	vertexCounter += 2;
	for (float i = 0.0f; (i < numSegments); i += 1.0f)
	{
		float angle = (PI * i * 2.0f) / numSegments;
		float nextAngle = (PI * (i + 1.0f) * 2.0f) / numSegments;
		float x1 = radius * sin(angle), y1 = radius * cos(angle);
		float x2 = radius * sin(nextAngle), y2 = radius * cos(nextAngle);
		// We actually generate the vertices used for the tower part AGAIN,
		// since we want to use different normals for the top and bottom
		Vertex v1, v2, v3, v4;
		v1.position = Vector3(x1, y1, -(height / 2.0f));
		v1.normal = Vector3(0.0f, 0.0f, -1.0f);
		v2.position = Vector3(x2, y2, height / 2.0f);
		v2.normal = Vector3(0.0f, 0.0f, 1.0f);
		v3.position = Vector3(x1, y1, height / 2.0f);
		v3.normal = Vector3(0.0f, 0.0f, 1.0f);
		v4.position = Vector3(x2, y2, -(height / 2.0f));
		v4.normal = Vector3(0.0f, 0.0f, -1.0f);

		generatedVertices.push_back(v1); generatedVertices.push_back(v2);
		generatedVertices.push_back(v3); generatedVertices.push_back(v4);

		generatedTriangles.push_back( Triangle(topIndex, vertexCounter + 2, vertexCounter + 1) ); // top
		generatedTriangles.push_back( Triangle(bottomIndex, vertexCounter + 3, vertexCounter) ); // bottom
		vertexCounter += 4;
	}
	return Surface(generatedVertices, generatedTriangles);
}

Surface	SurfaceFactory::createCone(float height, float radius, int numSegments)
{
	// Construct a cone using the given arguments
	VertexList generatedVertices;
	TriangleList generatedTriangles;
	int vertexCounter = 0;
	// Generate top and bottom vertices
	float halfHeight  (height / 2.0f);
	Vertex topCentre;
	topCentre.position = Vector3(0.0f, 0.0f, halfHeight);
	topCentre.normal = topCentre.position.normalise();
	generatedVertices.push_back(topCentre);
	Vertex bottomCentre;
	bottomCentre.position = Vector3(0.0f, 0.0f, -halfHeight);
	bottomCentre.normal = bottomCentre.position.normalise();
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

	return Surface(generatedVertices, generatedTriangles);
}

