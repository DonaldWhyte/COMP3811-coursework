#include "Dodecahedron.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
    
bool willShowLine(int counter)
{
	return ((counter % 6 != 0) );
}

Dodecahedron::Dodecahedron()
{
	vertices.push_back( Vector3(0.607f, 0.0f, 0.795f) );
	vertices.push_back( Vector3(0.188f, 0.566f, 0.795f) );
	vertices.push_back( Vector3(-0.491f, 0.357f, 0.795f) );
	vertices.push_back( Vector3(-0.491f, -0.357f, 0.795f) );
	vertices.push_back( Vector3(0.188f, -0.566f, 0.795f) );
	vertices.push_back( Vector3(0.982f, 0.0f, 0.188f) );
	vertices.push_back( Vector3(0.304f, 0.934f, 0.188f) );
	vertices.push_back( Vector3(-0.795f, 0.566f, 0.188f) );
	vertices.push_back( Vector3(-0.795f, -0.566f, 0.188f) );
	vertices.push_back( Vector3(0.304f, -0.934f, 0.188f) );
	vertices.push_back( Vector3(0.795f, 0.566f, -0.188f) );
	vertices.push_back( Vector3(-0.304f, 0.934f, -0.188f) );
	vertices.push_back( Vector3(-0.982f, 0.0f, -0.188f) );
	vertices.push_back( Vector3(-0.304f, -0.934f, -0.188f) );
	vertices.push_back( Vector3(0.795f, -0.566f, -0.188f) );
	vertices.push_back( Vector3(0.491f, 0.357f, -0.795f) );
	vertices.push_back( Vector3(-0.188f, 0.566f, -0.795f) );
	vertices.push_back( Vector3(-0.607f, 0.0f, -0.795f) );
	vertices.push_back( Vector3(-0.188f, -0.566f, -0.795f) );
	vertices.push_back( Vector3(0.491f, -0.357f, -0.795f) );

	lines.push_back( Line(1, 2) );
	lines.push_back( Line(2, 3) );
	lines.push_back( Line(3, 4) );
	lines.push_back( Line(4, 0) );
	lines.push_back( Line(10, 6) );
	lines.push_back( Line(6, 1) );
	lines.push_back( Line(0, 5) );
	lines.push_back( Line(6, 11) );
	lines.push_back( Line(11, 7) );
	lines.push_back( Line(7, 2) );
	lines.push_back( Line(7, 12) );
	lines.push_back( Line(8, 3) );
	lines.push_back( Line(8, 13) );
	lines.push_back( Line(13, 9) );
	lines.push_back( Line(9, 4) );
	lines.push_back( Line(9, 14) );
	lines.push_back( Line(14, 5) );
	lines.push_back( Line(16, 11) );
	lines.push_back( Line(10, 15) );
	lines.push_back( Line(16, 17) );
	lines.push_back( Line(17, 12) );
	lines.push_back( Line(17, 18) );
	lines.push_back( Line(18, 13) );
	lines.push_back( Line(18, 19) );
	lines.push_back( Line(19, 14) );
	lines.push_back( Line(19, 15) );
	lines.push_back( Line(12, 8) );
	lines.push_back( Line(5, 10) );
	lines.push_back( Line(16, 15) );
	lines.push_back( Line(0, 1) );

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

