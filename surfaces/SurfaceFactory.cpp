#include "SurfaceFactory.h"
#include <cmath>
#include <cstdlib>

/* Generates random float between 0 and 1 inclusive.
 * Declared in source file as it's currently not needed
 * outside of this translation unit.*/
float randomFloat()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

SurfaceFactory::SurfaceFactory(bool generateRandomColours) :
    generateRandomColours(generateRandomColours)
{
}

Surface* SurfaceFactory::createCylinder(float height, float radius, int numSegments)
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
	
		generatedTriangles.push_back( Triangle(vertexCounter + 2, vertexCounter + 1, vertexCounter) );
		generatedTriangles.push_back( Triangle(vertexCounter, vertexCounter + 1, vertexCounter + 3) );
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

		generatedTriangles.push_back( Triangle(vertexCounter + 1, vertexCounter + 2, topIndex) ); // top
		generatedTriangles.push_back( Triangle(vertexCounter, vertexCounter + 3, bottomIndex) ); // bottom
		vertexCounter += 4;
	}
	
    return generateSurface(generatedVertices, generatedTriangles);
}

Surface* SurfaceFactory::createCone(float height, float radius, int numSegments)
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
		generatedTriangles.push_back( Triangle(vertexCounter, vertexCounter + 1, 1) );
		// Triangle for bottom section
		generatedTriangles.push_back( Triangle(vertexCounter + 3, vertexCounter + 2, 0) );
		vertexCounter += 4;
	}

    return generateSurface(generatedVertices, generatedTriangles);
}

Surface* SurfaceFactory::createBox(float width, float height, float length)
{
    VertexList generatedVertices;
    TriangleList generatedTriangles;
    
    // Generate the eight vertices required for the box
    Vector3List vertexPositions;
    vertexPositions.reserve(8);
    vertexPositions.push_back( Vector3(0, 0, 0) );
    vertexPositions.push_back( Vector3(0, height, 0) );
    vertexPositions.push_back( Vector3(0, height, length) );
    vertexPositions.push_back( Vector3(0, 0, length) );
    vertexPositions.push_back( Vector3(width, 0, length) );
    vertexPositions.push_back( Vector3(width, height, length) );
    vertexPositions.push_back( Vector3(width, height, 0) );
    vertexPositions.push_back( Vector3(width, 0, 0) );                            
    generatedTriangles.reserve(vertexPositions.size());
    for (Vector3List::const_iterator it = vertexPositions.begin();
        (it != vertexPositions.end()); it++)
    {
        Vertex v;
        v.position = v.normal = (*it);
        generatedVertices.push_back(v);
    }
    // Generate fixed set of triangles for the surface
    generatedTriangles.push_back( Triangle(2, 3, 0) ); generatedTriangles.push_back( Triangle(0, 1, 2) );
    generatedTriangles.push_back( Triangle(3, 2, 5) ); generatedTriangles.push_back( Triangle(5, 4, 3) );
    generatedTriangles.push_back( Triangle(6, 1, 0) ); generatedTriangles.push_back( Triangle(0, 7, 6) );
    generatedTriangles.push_back( Triangle(4, 7, 0) ); generatedTriangles.push_back( Triangle(0, 3, 4) );
    generatedTriangles.push_back( Triangle(4, 5, 6) ); generatedTriangles.push_back( Triangle(6, 7, 4) );
    generatedTriangles.push_back( Triangle(5, 2, 1) ); generatedTriangles.push_back( Triangle(1, 6, 5) );

    return generateSurface(generatedVertices, generatedTriangles);
}

Surface* SurfaceFactory::createSphere(float radius, int numRings, int numQuadsPerRing)
{
    VertexList generatedVertices;
    TriangleList generatedTriangles;
    
    unsigned int vertexCounter = 0;
	for (unsigned int ring = 0; (ring < numRings); ring++)
	{
		// Per-ring parameters
		float phi = -(PI / 2.0f) + (static_cast<float>(ring) * (PI / numRings));
		float nextPhi = -(PI / 2.0f) + (static_cast<float>(ring + 1) * (PI / numRings));
		float cosPhi = cos(phi);
		float sinPhi = sin(phi);
		float cosNextPhi = cos(nextPhi);
		float sinNextPhi = sin(nextPhi);
		for (unsigned int quad = 0; (quad < numQuadsPerRing); quad++)
		{
			// Compute parameters for computing vertices
			float theta = static_cast<float>(quad) * ((2.0f * PI) / numQuadsPerRing);
			float nextTheta = static_cast<float>(quad + 1) * ((2.0f * PI) / numQuadsPerRing);
			float cosTheta = cos(theta);
			float sinTheta = sin(theta);
			float cosNextTheta = cos(nextTheta);
			float sinNextTheta = sin(nextTheta);
			// Compute vertex positions and normals
			Vertex v1, v2, v3, v4;
			// phi_i, theta_j
			v1.position = Vector3(radius * cosPhi * cosTheta, radius * cosPhi * sinTheta, radius * sinPhi);
			v1.normal = v1.position.normalise();
			v1.texCoord = computeSphereTexCoord(v1.normal);
			// phi_i, theta_j+1
			v2.position = Vector3(radius * cosPhi * cosNextTheta, radius * cosPhi * sinNextTheta, radius * sinPhi);
			v2.normal = v2.position.normalise();
			v2.texCoord = computeSphereTexCoord(v2.normal);
			// phi_i+1, theta_j+1
			v3.position = Vector3(radius * cosNextPhi * cosNextTheta, radius * cosNextPhi * sinNextTheta, radius * sinNextPhi);
			v3.normal = v3.position.normalise();
			v3.texCoord = computeSphereTexCoord(v3.normal);
			// phi_i+1, theta_j
			v4.position = Vector3(radius * cosNextPhi * cosTheta, radius * cosNextPhi * sinTheta, radius * sinNextPhi);
			v4.normal = v4.position.normalise();
			v4.texCoord = computeSphereTexCoord(v4.normal);
			generatedVertices.push_back(v1); generatedVertices.push_back(v2);
			generatedVertices.push_back(v3); generatedVertices.push_back(v4);

			// Create two triangles to render the quad
			generatedTriangles.push_back( Triangle(vertexCounter, vertexCounter+1, vertexCounter+2) );
			generatedTriangles.push_back( Triangle(vertexCounter+3, vertexCounter, vertexCounter+2) );
			vertexCounter += 4;
		}
	}    
    
    return generateSurface(generatedVertices, generatedTriangles);
}

Surface* SurfaceFactory::generateSurface(const VertexList& verts, const TriangleList& tris)
{
    Vector3 colour;
    if (generateRandomColours)
        colour = Vector3(randomFloat(), randomFloat(), randomFloat());
    else
        colour = Vector3(1.0f, 0.0f, 0.0f);
    
    return new Surface(verts, tris, colour);
}
    
TexCoord SurfaceFactory::computeSphereTexCoord(const Vector3& posOnSphere)
{
	float s = 0.5f + (atan2(posOnSphere.z, posOnSphere.x) / (2.0f * PI));
	float t = 0.5f - (asin(posOnSphere.y) / PI);
	return TexCoord(s, t); 
}


