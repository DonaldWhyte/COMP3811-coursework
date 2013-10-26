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

	enum GeometryType
	{
		MESH_GEOM_POINTS = 0,
		MESH_GEOM_LINES,
		MESH_GEOM_TRIANGLES
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
	// Controls if per-face surface normals are being used
	virtual bool usingPerFaceNormals() const;
	virtual void setPerFaceNormals(bool usePerFace);
	// Controls if normals are rendered on mesh
	bool showingNormals() const;
	void showNormals(bool willShow);
	// Controls what type of geometry is rendered
	GeometryType geometryType() const;
	void setGeometryType(GeometryType newGeomType);

	void renderVertex(const Vertex& v);
	void renderTriangle(const VertexList& verticesToUse, const Triangle& tri);
	void renderPoints(const VertexList& vertices);
	void renderLines(const VertexList& vertices, const TriangleList& triangles);
	void renderTriangles(const VertexList& vertices, const TriangleList& triangles);
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
	GeometryType geomType;
	Texture* surfaceTexture;

	bool drawNormals;
	bool useSurfaceNormals;

};

#endif
