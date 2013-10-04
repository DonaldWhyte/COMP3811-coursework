#ifndef GL_POLYGON_WIDGET_H
#define GL_POLYGON_WIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include "GLPolygon.h"

/* Widget that uses OpenGL to render the polygon. */
class GLPolygonWidget : public QGLWidget
{

	Q_OBJECT

public:
	GLPolygonWidget(QWidget* parent, GLPolygon* initialPolygon);
	void setPolygon(GLPolygon* newPolygon);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

	/* Used to move and rotate the polygon. */
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);

private:
	/* Determines how much the polygon should be moved/rotated
 	 * when a mosue event occurs. Returns true if mouse event
 	 * changed state of the polygon.  */
	bool processMouseEvent(QMouseEvent* event);

	GLPolygon* polygon;
	float oldMouseY;

signals:
	/* This signal is fired if this widget changed
 	 * the state of the polygon. */
	void changed();

};

#endif
