#ifndef GL_APPLICATION_CONTROLLER_H
#define GL_APPLICATION_CONTROLLER_H

#include <QTimer>
#include "GLWindow.h"
#include "Drawable.h"

/* Controller for main program. */
class GLApplicationController : public QObject
{

	Q_OBJECT

public:
	GLApplicationController(GLWindow* window, Drawable* drawableObject);

public slots:
	void canvasWidgetChanged();
	void xSliderChanged(int newValue);
	void ySliderChanged(int newValue);
	void rotationDialChanged(int newValue);
	void animationCheckBoxChanged(int state);
	void pointRadioChanged(bool checked);
	void lineRadioChanged(bool checked);
	void triangleRadioChanged(bool checked);
	void colourTrianglesChanged(int newState);
	void nextAnimationFrame(); // used to provide animation to objects 

private:
	// Length of each frame for polygon animation. This is in milliseconds
	static const double ANIMATION_FRAME_LENGTH = 16.67;

	GLWindow* window;
	Drawable* drawable;
	QTimer* animationTimer;

	// If set to true, then the polygon drawn will be animated
	bool animating;
	// If set to true, triangles composing the faces of polyhedra
	// will be coloured differently
	bool colourTriangles;

};

#endif
