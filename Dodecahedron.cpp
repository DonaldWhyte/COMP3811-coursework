#include"Dodecahedron.h"
#include <math.h>
#include <iostream>
    
Dodecahedron::Dodecahedron()
{
    vertices.push_back( Vector3(0.607, 0.000, 0.795) );
    vertices.push_back( Vector3(0.188, 0.577, 0.795) );
    vertices.push_back( Vector3(-0.491, 0.357, 0.795) );
    vertices.push_back( Vector3(-0.491, -0.357, 0.795) );
    vertices.push_back( Vector3(0.188, -0.577, 0.795) );
    vertices.push_back( Vector3(0.982, 0.000, 0.188) );
    vertices.push_back( Vector3(0.304, 0.934, 0.188) );
    vertices.push_back( Vector3(-0.795, 0.577, 0.188) );
    vertices.push_back( Vector3(-0.795, -0.577, 0.188) );
    vertices.push_back( Vector3(0.304, -0.934, 0.188) );
    vertices.push_back( Vector3(0.795, 0.577, -0.188) );
    vertices.push_back( Vector3(-0.304, 0.934, -0.188) );
    vertices.push_back( Vector3(-0.982, 0.000, -0.188) );
    vertices.push_back( Vector3(-0.304, -0.934, -0.188) );
    vertices.push_back( Vector3(0.795, -0.577, -0.188) );
    vertices.push_back( Vector3(0.491, 0.357, -0.795) );
    vertices.push_back( Vector3(-0.188, 0.577, -0.795) );
    vertices.push_back( Vector3(-0.607, 0.000, -0.795) );
    vertices.push_back( Vector3(-0.188, -0.577, -0.795) );
    vertices.push_back( Vector3(0.491, -0.357, -0.795) );
    triangles.push_back( Triangle(0, 1, 2) );
    triangles.push_back( Triangle(0, 2, 3) );
    triangles.push_back( Triangle(0, 3, 4) );
    triangles.push_back( Triangle(5, 10, 6) );
    triangles.push_back( Triangle(5, 6, 1) );
    triangles.push_back( Triangle(5, 1, 0) );
    triangles.push_back( Triangle(6, 11, 7) );
    triangles.push_back( Triangle(6, 7, 2) );
    triangles.push_back( Triangle(6, 2, 1) );
    triangles.push_back( Triangle(7, 12, 8) );
    triangles.push_back( Triangle(7, 8, 3) );
    triangles.push_back( Triangle(7, 3, 2) );
    triangles.push_back( Triangle(8, 13, 9) );
    triangles.push_back( Triangle(8, 9, 4) );
    triangles.push_back( Triangle(8, 4, 3) );
    triangles.push_back( Triangle(9, 14, 5) );
    triangles.push_back( Triangle(9, 5, 0) );
    triangles.push_back( Triangle(9, 0, 4) );
    triangles.push_back( Triangle(15, 16, 11) );
    triangles.push_back( Triangle(15, 11, 6) );
    triangles.push_back( Triangle(15, 6, 10) );
    triangles.push_back( Triangle(16, 17, 12) );
    triangles.push_back( Triangle(16, 12, 7) );
    triangles.push_back( Triangle(16, 7, 11) );
    triangles.push_back( Triangle(17, 18, 13) );
    triangles.push_back( Triangle(17, 13, 8) );
    triangles.push_back( Triangle(17, 8, 12) );
    triangles.push_back( Triangle(18, 19, 14) );
    triangles.push_back( Triangle(18, 14, 9) );
    triangles.push_back( Triangle(18, 9, 13) );
    triangles.push_back( Triangle(19, 15, 10) );
    triangles.push_back( Triangle(19, 10, 5) );
    triangles.push_back( Triangle(19, 5, 14) );
    triangles.push_back( Triangle(19, 18, 17) );
    triangles.push_back( Triangle(19, 17, 16) );
    triangles.push_back( Triangle(19, 16, 15) );
}

const Vector3List& Dodecahedron::getVertices() const
{
	return vertices;
}

const LineList& Dodecahedron::getLines() const
{
	return lines;
}

const TriangleList& Dodecahedron::getTriangles() const
{
	return triangles;
}

