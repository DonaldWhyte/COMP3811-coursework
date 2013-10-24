#include "Cone.h"
#include <math.h>

Cone::Cone(float height, float radius, int numSegments) : Mesh()
{
	// Construct a cone using the given argument
	VertexList generatedVertices;
	TriangleList generatedTriangles;
	int vertexCounter = 0;
	// Generate top vertex
	Vertex topCentre;
	topCentre.position = Vector3(0.0f, 0.0f, height);
	topCentre.normal = topCentre.position.normalise();
	generatedVertices.push_back(topCentre);
	vertexCounter += 1;	

	// Generate the 'tower' part of the cone
	for (float i = 0.0f; (i < numSegments); i += 1.0f)
	{
		float angle = (PI * i * 2.0f) / numSegments;
		float nextAngle = (PI * (i + 1.0f) * 2.0f) / numSegments;
		float x1 = radius * sin(angle), y1 = radius * cos(angle);
		float x2 = radius * sin(nextAngle), y2 = radius * cos(nextAngle);
		
		Vertex v1, v2;
		v1.position = Vector3(x1, y1, 0.0f);
		v1.normal = Vector3(x1, y1, 0.0f).normalise();
		v2.position = Vector3(x2, y2, 0.0f);
		v2.normal = Vector3(x2, y2, 0.0f).normalise();
		generatedVertices.push_back(v1);
		generatedVertices.push_back(v2);
	
		generatedTriangles.push_back( Triangle(0, vertexCounter, vertexCounter + 1) );
		vertexCounter += 2;
	}
	// Generate top and bottom sections
	Vertex bottomCentre;
	bottomCentre.position = Vector3(0.0f, 0.0f, 0.0f);
	bottomCentre.normal = bottomCentre.position.normalise();
	generatedVertices.push_back(bottomCentre);
	vertexCounter += 1;
	// each PAIR of vertices and the central vertex is used for triangle
	for (unsigned int i = 0; (i < numSegments - 1); i++)
	{
		int index1 = (i * 2) + 1;
		int index2 = vertexCounter - 1;
		int index3 = (i * 2) + 2;
		Triangle bottomTri(index1, index2, index3);
		generatedTriangles.push_back(bottomTri);
	}
	// last triangle to fill bottom section
	generatedTriangles.push_back( Triangle(((numSegments -1) * 2) + 1, vertexCounter - 1, 1) );
	
	vertexCounter += 2;

	setVertices(generatedVertices);
	setTriangles(generatedTriangles);
}

Cone::~Cone()
{
}

TexCoord Cone::computeTexCoord(const Vector3& posOnCone)
{
	//float theta = (atan(1.0f * posOnCone.y, 1.5f * posOnCone.x) + (PI * 0.5f)) / PI;
	//return TexCoord(theta, -(posOnCone.z + 0.5f)); 
	return TexCoord(0.0f, 0.0f);
}
