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
		v1.position = Vector3(x1, y1, 0.0f);
		v1.normal = Vector3(x1, y1, 0.0f).normalise();
		v2.position = Vector3(x2, y2, height);
		v2.normal = Vector3(x2, y2, 0.0f).normalise();
		v3.position = Vector3(x1, y1, height);
		v3.normal = Vector3(x1, y1, 0.0f).normalise();
		v4.position = Vector3(x2, y2, 0.0f);
		v4.normal = Vector3(x2, y2, 0.0f).normalise();
		generatedVertices.push_back(v1); generatedVertices.push_back(v2);
		generatedVertices.push_back(v3); generatedVertices.push_back(v4);
	
		generatedTriangles.push_back( Triangle(vertexCounter, vertexCounter + 1, vertexCounter + 2) );
		generatedTriangles.push_back( Triangle(vertexCounter + 3, vertexCounter + 1, vertexCounter) );
		vertexCounter += 4;
	}
	// Generate top and bottom sections
	Vertex topCentre, bottomCentre;
	topCentre.position = Vector3(0.0f, 0.0f, height);
	topCentre.normal = topCentre.position.normalise();
	bottomCentre.position = Vector3(0.0f, 0.0f, 0.0f);
	bottomCentre.normal = bottomCentre.position.normalise();
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
	generatedTriangles.push_back( Triangle(vertexCounter + 1, 3, ((numSegments - 1) * 4)) );
	
	vertexCounter += 2;
	
	setVertices(generatedVertices);
	setTriangles(generatedTriangles);
}

Cylinder::~Cylinder()
{
}

TexCoord Cylinder::computeTexCoord(const Vector3& posOnCylinder)
{
	//float theta = (atan(1.0f * posOnCylinder.y, 1.5f * posOnCylinder.x) + (PI * 0.5f)) / PI;
	//return TexCoord(theta, -(posOnCylinder.z + 0.5f)); 
	return TexCoord(0.0f, 0.0f);
}
