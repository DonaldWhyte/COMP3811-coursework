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

bool GLPolygonWidget::processMouseEvent(QMouseEvent* event)
{
	bool changeMade = false; // set to true if state of polygon changed

	// Check which mouse buttons are pressed
	if (event->buttons() & Qt::LeftButton) //  if left button pressed
	{
		static const float radius = 0.75;
		float newX = (static_cast<float>(event->x()) / this->width()) - (radius / 2);
		float newY = -(static_cast<float>(event->y()) / this->height()) + (radius / 2);
		polygon->setX(newX);
		polygon->setY(newY);
		changeMade = true;
	}
	if (event->buttons() & Qt::RightButton) // if right button pressed
	{
		float difference = oldMouseY - event->y();
		float newDegrees = polygon->rotationDegrees() + difference;
		polygon->setRotationDegrees(newDegrees);
		changeMade = true;
	}

	// If no mouse button pressed and no change made, just return false
	if (!changeMade) return false;

	// Ensure polygon does not go out of bounds
	if (polygon->x() < -1.0f) polygon->setX(-1.0f);
	else if (polygon->x() > 1.0f) polygon->setX(1.0f);
	if (polygon->y() < -1.0f) polygon->setY(-1.0f);
	else if (polygon->y() > 1.0f) polygon->setY(1.0f);
	if (polygon->rotationDegrees() < 0.0f || polygon->rotationDegrees() > 360.0f)
		polygon->setRotationDegrees(0.0f);
	
	// Accept event so it's not processed further and redraw widget to reflect changes
	event->accept();
	// Also keep track of the Y value for later use
	oldMouseY = event->y();

	return true; // change made to return true
}

void GLPolygonWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (processMouseEvent(event))
		emit changed();
}

void GLPolygonWidget::mousePressEvent(QMouseEvent* event)
{
	if (processMouseEvent(event))
		emit changed();
}
