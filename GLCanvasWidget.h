#ifndef GL_CANVAS_WIDGET_H
#define GL_CANVAS_WIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include "Drawable.h"

/* Widget that uses OpenGL to render a single object. */
class GLCanvasWidget : public QGLWidget
{

	Q_OBJECT

public:
	GLCanvasWidget(QWidget* parent, Drawable* drawableObject);
	void setDrawable(Drawable* newDrawable);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

	/* Used to move and rotate the polygon. */
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);

private:
	/* Determines how much the polygon should be moved/rotated
 	 * when a mouse event occurs. Returns true if mouse event
 	 * changed state of the polygon.  */
	bool processMouseEvent(QMouseEvent* event);

	Drawable* drawable;
	float oldMouseY;

signals:
	/* This signal is fired if this widget changed
 	 * the state of the polygon. */
	void changed();

};

#endif
