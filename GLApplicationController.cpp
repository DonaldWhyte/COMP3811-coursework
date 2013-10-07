#include <QCoreApplication>
#include "GLApplicationController.h"

#include <typeinfo>
#include "GLPlatonicSolid.h"

GLApplicationController::GLApplicationController(GLWindow* window, Drawable* drawableObject)
	: window(window), drawable(drawableObject), animating(false)
{
	connect(window->canvasWidget, SIGNAL(changed()),
		this, SLOT(canvasWidgetChanged()));
	connect(window->actionQuit, SIGNAL(triggered()),
		QCoreApplication::instance(), SLOT(quit()));
	connect(window->xSlider, SIGNAL(valueChanged(int)),
		this, SLOT(xSliderChanged(int)));
	connect(window->ySlider, SIGNAL(valueChanged(int)),
		this, SLOT(ySliderChanged(int)));
	connect(window->rotationDial, SIGNAL(valueChanged(int)),
		this, SLOT(rotationDialChanged(int)));
	connect(window->animationCheckBox, SIGNAL(stateChanged(int)),
		this, SLOT(animationCheckBoxChanged(int)));

	connect(window->pointRadio, SIGNAL(clicked(bool)),
		this, SLOT(pointRadioChanged(bool)));
	connect(window->lineRadio, SIGNAL(clicked(bool)),
		this, SLOT(lineRadioChanged(bool)));
	connect(window->triangleRadio, SIGNAL(clicked(bool)),
		this, SLOT(triangleRadioChanged(bool)));
	connect(window->colourTrianglesCheckBox, SIGNAL(stateChanged(int)),
		this, SLOT(colourTrianglesChanged(int)));

	animationTimer = new QTimer(this);
	connect(animationTimer, SIGNAL(timeout()), this, SLOT(nextAnimationFrame()));
	animationTimer->start(ANIMATION_FRAME_LENGTH);
}

void GLApplicationController::canvasWidgetChanged()
{
	window->resetInterface();
}

void GLApplicationController::xSliderChanged(int newValue)
{
	float newX = static_cast<float>(newValue) / 100.0f;
	drawable->setX(newX);
	window->resetInterface();
}

void GLApplicationController::ySliderChanged(int newValue)
{
	float newY = static_cast<float>(newValue) / 100.0f;
	drawable->setY(newY);
	window->resetInterface();
}

void GLApplicationController::rotationDialChanged(int newValue)
{
	drawable->setRotationDegrees( static_cast<float>(newValue) );
	window->resetInterface();
}

void GLApplicationController::animationCheckBoxChanged(int newState)
{
	animating = (newState == Qt::Checked);
}

void GLApplicationController::pointRadioChanged(bool clicked)
{
	if (clicked)
	{
		drawable->setRenderMethod(RENDER_METHOD_POINTS);
		window->resetInterface();
	}
}

void GLApplicationController::lineRadioChanged(bool clicked)
{
	if (clicked)
	{
		drawable->setRenderMethod(RENDER_METHOD_LINES);
		window->resetInterface();
	}
}

void GLApplicationController::triangleRadioChanged(bool clicked)
{
	if (clicked)
	{
		drawable->setRenderMethod(RENDER_METHOD_TRIANGLES);
		window->resetInterface();
	}	
}

void GLApplicationController::colourTrianglesChanged(int newState)
{
	colourTriangles = (newState == Qt::Checked);
	// Check type of drawable -- if it's a platonic solid, update its state
	try
	{
		GLPlatonicSolid* platonicSolid = dynamic_cast<GLPlatonicSolid*>(drawable);
		platonicSolid->setColourTriangles(colourTriangles);
	}
	catch (const std::bad_cast& ex) { } // ignore casting error!

	window->resetInterface();
}

void GLApplicationController::nextAnimationFrame()
{
	if (!animating) return;

	float degrees = drawable->rotationDegrees();
	if (degrees < 0.0f || degrees > 360.0f)
		degrees = 0.0f;
	drawable->setRotationDegrees( degrees + 1.0f );

	window->resetInterface();
}
