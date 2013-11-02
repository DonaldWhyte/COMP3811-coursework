#include <math.h>

#include "GLCanvasWidget.h"
#include "Geometry.h"

GLCanvasWidget::GLCanvasWidget(QWidget* parent, Drawable* drawableObject) :
	QGLWidget(parent), drawable(drawableObject), oldMouseY(0.0f)
{
	setMouseTracking(true);
}

void GLCanvasWidget::setDrawable(Drawable* newDrawable)
{
	drawable = newDrawable;
}

void GLCanvasWidget::setLightingModel(LightingModel lModel)
{
	lightingManager.setLightingModel(lModel);
}

void GLCanvasWidget::initializeGL()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	// Enable back-face culling for efficiency
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// Will make OpenGL automatically normalise vertex normals
	glEnable(GL_NORMALIZE);

	glPointSize(5.0f);
	glLineWidth(3.0f);

	setupProjection(this->width(), this->height());
	setupViewport(this->width(), this->height());

	lightingManager.initialise();
//	lightingManager.setLightingModel(LIGHTING_MODEL_SMOOTH);	
}

void GLCanvasWidget::resizeGL(int width, int height)
{
	setupProjection(width, height);
	setupViewport(width, height);
}

void GLCanvasWidget::setupProjection(int width, int height)
{
	// Setup orthographic projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = static_cast<double>(width) / height;
	gluPerspective(45.5, aspectRatio, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
}

void GLCanvasWidget::setupViewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

#include <iostream>
void GLCanvasWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Clear modelview matrix before rendering the scene
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawable->render();

	glFlush();
}

bool GLCanvasWidget::processMouseEvent(QMouseEvent* event)
{
	bool changeMade = false; // set to true if state of drawable changed

	// Check which mouse buttons are pressed
	if (event->buttons() & Qt::LeftButton) //  if left button pressed
	{
		static const float radius = 0.75;
		float newX = (static_cast<float>(event->x()) / this->width()) - (radius / 2);
		float newY = -(static_cast<float>(event->y()) / this->height()) + (radius / 2);
		drawable->setX(newX);
		drawable->setY(newY);
		changeMade = true;
	}
	if (event->buttons() & Qt::RightButton) // if right button pressed
	{
		float difference = oldMouseY - event->y();
		float newDegrees = drawable->zRotation() + difference;
		drawable->setZRotation(newDegrees);
		changeMade = true;
	}

	// If no mouse button pressed and no change made, just return false
	if (!changeMade) return false;

	// Ensure drawable does not go out of bounds
	if (drawable->x() < -1.0f) drawable->setX(-1.0f);
	else if (drawable->x() > 1.0f) drawable->setX(1.0f);
	if (drawable->y() < -1.0f) drawable->setY(-1.0f);
	else if (drawable->y() > 1.0f) drawable->setY(1.0f);
	float zRotation = drawable->zRotation();
	if (zRotation < 0.0f || zRotation > 360.0f)
		drawable->setZRotation(0.0f);
	
	// Accept event so it's not processed further and redraw widget to reflect changes
	event->accept();
	// Also keep track of the Y value for later use
	oldMouseY = event->y();

	return true; // change made to return true
}

void GLCanvasWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (processMouseEvent(event))
		emit changed();
}

void GLCanvasWidget::mousePressEvent(QMouseEvent* event)
{
	if (processMouseEvent(event))
		emit changed();
}
