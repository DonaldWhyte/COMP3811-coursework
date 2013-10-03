#ifndef GL_POLYGON_CONTROLLER_H
#define GL_POLYGON_CONTROLLER_H

#include <QTimer>
#include "GLPolygonWindow.h"
#include "GLPolygon.h"

/* Controller for main program. */
class GLPolygonController : public QObject
{

	Q_OBJECT

public:
	GLPolygonController(GLPolygonWindow* window, GLPolygon* polygon);

public slots:
	void polygonWidgetChanged();
	void nVerticesSliderChanged(int newValue);
	void xSliderChanged(int newValue);
	void ySliderChanged(int newValue);
	void rotationDialChanged(int newValue);
	void animationCheckBoxChanged(int state);
	void nextAnimationFrame(); // used 

private:
	// Length of each frame for polygon animation. This is in milliseconds
	static const double ANIMATION_FRAME_LENGTH = 16.67;

	GLPolygonWindow* window;
	GLPolygon* polygon;
	QTimer* animationTimer;

	// If set to true, then the polygon drawn will be animated
	bool animating;

};

#endif
