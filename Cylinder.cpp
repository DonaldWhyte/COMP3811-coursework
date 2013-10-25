#include "Cylinder.h"
#include <math.h>

Cylinder::Cylinder(float height, float radius, int numSegments) : Mesh()
{
	// Construct a cylinder using the given argument
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
		v1.texCoord = computeTexCoord(angle, v1.position.z, height);
		v2.position = Vector3(x2, y2, height / 2.0f);
		v2.normal = Vector3(x2, y2, 0.0f).normalise();
		v2.texCoord = computeTexCoord(nextAngle, v2.position.z, height);
		v3.position = Vector3(x1, y1, height / 2.0f);
		v3.normal = Vector3(x1, y1, 0.0f).normalise();
		v3.texCoord = computeTexCoord(angle, v3.position.z, height);
		v4.position = Vector3(x2, y2, -(height / 2.0f));
		v4.normal = Vector3(x2, y2, 0.0f).normalise();
		v4.texCoord = computeTexCoord(nextAngle, v4.position.z, height);
		generatedVertices.push_back(v1); generatedVertices.push_back(v2);
		generatedVertices.push_back(v3); generatedVertices.push_back(v4);
	
		generatedTriangles.push_back( Triangle(vertexCounter, vertexCounter + 1, vertexCounter + 2) );
		generatedTriangles.push_back( Triangle(vertexCounter + 3, vertexCounter + 1, vertexCounter) );
		vertexCounter += 4;
	}
	// Generate top and bottom sections
	Vertex topCentre, bottomCentre;
	topCentre.position = Vector3(0.0f, 0.0f, height / 2.0f);
	topCentre.normal = topCentre.position.normalise();
	topCentre.texCoord = TexCoord(0.5f, 0.5f);
	bottomCentre.position = Vector3(0.0f, 0.0f, -(height / 2.0f));
	bottomCentre.normal = bottomCentre.position.normalise();
	bottomCentre.texCoord = TexCoord(0.5f, 0.5f);
	generatedVertices.push_back(topCentre); generatedVertices.push_back(bottomCentre);
	// each PAIR of vertices and the central vertex is used for triangle
	for (unsigned int i = 0; (i < numSegments - 1); i++)
	{
		Triangle top(vertexCounter, (i * 4) + 2, (i * 4) + 1);
		Triangle bottom(vertexCounter + 1, (i * 4) + 3, (i * 4) + 0);
		generatedTriangles.push_back(top);
		generatedTriangles.push_back(bottom);
	}
	// last two triangles to fill top/bottom sections
	generatedTriangles.push_back( Triangle(vertexCounter, ((numSegments - 1) * 4) + 2, 1) );
	generatedTriangles.push_back( Triangle(vertexCounter + 1, 0, ((numSegments - 1) * 4)) );
	
	vertexCounter += 2;
	
	setVertices(generatedVertices);
	setTriangles(generatedTriangles);
}

Cylinder::~Cylinder()
{
}

TexCoord Cylinder::computeTexCoord(float angle, float currentHeight, float totalHeight)
{
	return TexCoord((angle / (2.0f * PI)), // s
		(currentHeight + (totalHeight / 2.0f)) / totalHeight // t
	);
}
