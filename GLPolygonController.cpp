#include <QCoreApplication>
#include "GLPolygonController.h"

GLPolygonController::GLPolygonController(GLPolygonWindow* window, GLPolygon* polygon)
	: window(window), polygon(polygon), animating(false)
{
	connect(window->polygonWidget, SIGNAL(changed()),
		this, SLOT(polygonWidgetChanged()));
	connect(window->actionQuit, SIGNAL(triggered()),
		QCoreApplication::instance(), SLOT(quit()));
	connect(window->nVerticesSlider, SIGNAL(valueChanged(int)),
		this, SLOT(nVerticesSliderChanged(int)));
	connect(window->xSlider, SIGNAL(valueChanged(int)),
		this, SLOT(xSliderChanged(int)));
	connect(window->ySlider, SIGNAL(valueChanged(int)),
		this, SLOT(ySliderChanged(int)));
	connect(window->rotationDial, SIGNAL(valueChanged(int)),
		this, SLOT(rotationDialChanged(int)));
	connect(window->animationCheckBox, SIGNAL(stateChanged(int)),
		this, SLOT(animationCheckBoxChanged(int)));

	animationTimer = new QTimer(this);
	connect(animationTimer, SIGNAL(timeout()), this, SLOT(nextAnimationFrame()));
	animationTimer->start(ANIMATION_FRAME_LENGTH);
}

void GLPolygonController::polygonWidgetChanged()
{
	window->resetInterface();
}

void GLPolygonController::nVerticesSliderChanged(int newValue)
{
	polygon->setNumVertices(newValue);
	window->resetInterface();
}

void GLPolygonController::xSliderChanged(int newValue)
{
	float newX = static_cast<float>(newValue) / 100.0f;
	polygon->setX(newX);
	window->resetInterface();
}

void GLPolygonController::ySliderChanged(int newValue)
{
	float newY = static_cast<float>(newValue) / 100.0f;
	polygon->setY(newY);
	window->resetInterface();
}

void GLPolygonController::rotationDialChanged(int newValue)
{
	polygon->setRotationDegrees( static_cast<float>(newValue) );
	window->resetInterface();
}

void GLPolygonController::animationCheckBoxChanged(int newState)
{
	animating = (newState == Qt::Checked);
}

void GLPolygonController::nextAnimationFrame()
{
	if (!animating) return;

	float degrees = polygon->rotationDegrees();
	if (degrees < 0.0f || degrees > 360.0f)
		degrees = 0.0f;
	polygon->setRotationDegrees( degrees + 1.0f );

	window->resetInterface();
}
