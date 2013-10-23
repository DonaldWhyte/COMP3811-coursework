#ifndef MESH_H
#define MESH_H

#include "Drawable.h"
#include "Geometry.h"
#include "Texture.h"

class Mesh : public Drawable
{

public:
	enum Colouring
	{
		MESH_COLOUR_SAME = 0,
		MESH_ALTERNATING_TRIANGLES,
		MESH_FLAT_SHADING,
		MESH_SMOOTH_SHADING,
		MESH_TEXTURE
	};

	Mesh();
	virtual ~Mesh();

	/* Getters and setters for geometry. */
	const VertexList& vertices() const;
	void setVertices(const VertexList& newVerts);
	const TriangleList& triangles() const;
	void setTriangles(const TriangleList& triangles); 
	/* Getters and setters for surface colouring. */
	Colouring colouring() const;
	void setColouring(Colouring newColouring);
	Texture* texture() const;
	void setTexture(Texture* texture);

	bool usingPerFaceNormals() const;
	void setPerFaceNormals(bool usePerFace);

	void renderVertex(const Vertex& v);
	void renderTriangle(const VertexList& verticesToUse, const Triangle& tri);
	void renderPoints(const VertexList& vertices);
	void renderNormals(const VertexList& vertices);
	void render();

private:
	/* Return list of normals for given vertices (returned list
 	 * has same size as vertex list given) which are the normals
 	 * of the CORRESPONDING SURFACE THE VERTEX IS PART OF.
 	 * NOTE: This assumes that NO vertices are shared between triangles.
 	 */
	Vector3List computeSurfaceNormals(const VertexList& vertices, const TriangleList& triangles);

	static const float NORMAL_SCALING_FACTOR = 0.05f;

	VertexList verts;
	TriangleList tris;
	Colouring triangleColouring;
	Texture* surfaceTexture;

	bool useSurfaceNormals;

};

#endif
