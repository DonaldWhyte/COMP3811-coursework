#include "GLPolygonWidget.h"

GLPolygonWidget::GLPolygonWidget(QWidget* parent, GLPolygon* initialPolygon) :
	QGLWidget(parent), polygon(initialPolygon), oldMouseY(0.0f)
{
	setMouseTracking(true);
}

void GLPolygonWidget::setPolygon(GLPolygon* newPolygon)
{
	polygon = newPolygon;
}

void GLPolygonWidget::initializeGL()
{
	glClearColor(0.3, 0.3, 0.3, 0.0);
}

void GLPolygonWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
}

void GLPolygonWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);

	polygon->render();

	glFlush();
}

void GLPolygonWidget::processMouseEvent(QMouseEvent* event)
{
	// Check which mouse buttons are pressed
	if (event->buttons() & Qt::LeftButton) //  if left button pressed
	{
		static const float radius = 0.75;
		float newX = (static_cast<float>(event->x()) / this->width()) - (radius / 2);
		float newY = -(static_cast<float>(event->y()) / this->height()) + (radius / 2);
		polygon->setX(newX);
		polygon->setY(newY);
	}
	if (event->buttons() & Qt::RightButton) // if right button pressed
	{
		float difference = oldMouseY - event->y();
		float newDegrees = polygon->rotationDegrees() + difference;
		polygon->setRotationDegrees(newDegrees);
	}

	// Ensure polygon does not go out of bounds
	if (polygon->x() < -1.0f) polygon->setX(-1.0f);
	else if (polygon->x() > 1.0f) polygon->setX(1.0f);
	if (polygon->y() < -1.0f) polygon->setY(-1.0f);
	else if (polygon->y() > 1.0f) polygon->setY(1.0f);
	if (polygon->rotationDegrees() < 0.0f || polygon->rotationDegrees() > 360.0f)
		polygon->setRotationDegrees(0.0f);
	
	// Accept event so it's not processed further and redraw widget to reflect changes
	event->accept();
	repaint();
	// Also keep track of the Y value for later use
	oldMouseY = event->y();
}

void GLPolygonWidget::mouseMoveEvent(QMouseEvent* event)
{
	processMouseEvent(event);
	emit changed();
}

void GLPolygonWidget::mousePressEvent(QMouseEvent* event)
{
	processMouseEvent(event);
	emit changed();
}
