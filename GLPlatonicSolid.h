#ifndef GL_TETRA_H
#define GL_TETRA_H

enum RenderMethod
{
	RENDER_METHOD_POINTS = 0,
	RENDER_METHOD_LINES,
	RENDER_METHOD_TRIANGLES
};

enum PlatonicSolidType
{
	PLATONIC_TETRAHEDRON = 0,
	PLATONIC_CUBE,
	PLATONIC_OCTAHEDRON,
	PLATONIC_DODECAHEDRON,
	PLATONIC_ICOSAHEDRON
};

class GLPlatonicSolid
{

public:
	GLPlatonicSolid(PlatonicSolidType type = PLATONIC_CUBE, RenderMethod method = RENDER_METHOD_TRIANGLES);

	RenderMethod renderMethod() const;
	void setRenderMethod(RenderMethod newMethod);

	PlatonicSolidType type() const;
	void setType(PlatonicSolidType newType);

	/* Draw platonic solid on screen. */
	void render() const;

private:
	RenderMethod method;
	PlatonicSolidType solidType;

};

#endif
