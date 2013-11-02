#include <QCoreApplication>
#include "GLApplicationController.h"

#include <typeinfo>
#include "Sphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Torus.h"

GLApplicationController::GLApplicationController(GLWindow* window, Drawable* drawableObject)
	: window(window), drawable(drawableObject), animating(false), skeletalAnimationPlaying(false)
{
	connect(window->canvasWidget, SIGNAL(changed()),
		this, SLOT(canvasWidgetChanged()));
	connect(window->actionQuit, SIGNAL(triggered()),
		QCoreApplication::instance(), SLOT(quit()));
	connect(window->xRotSlider, SIGNAL(valueChanged(int)),
		this, SLOT(xRotSliderChanged(int)));
	connect(window->yRotSlider, SIGNAL(valueChanged(int)),
		this, SLOT(yRotSliderChanged(int)));
	connect(window->zRotSlider, SIGNAL(valueChanged(int)),
		this, SLOT(zRotSliderChanged(int)));
	connect(window->animationCheckBox, SIGNAL(stateChanged(int)),
		this, SLOT(animationCheckBoxChanged(int)));
	connect(window->skeletalAnimationCheckBox, SIGNAL(stateChanged(int)),
		this, SLOT(skeletalAnimationCheckBoxChanged(int)));

	animationTimer = new QTimer(this);
	connect(animationTimer, SIGNAL(timeout()), this, SLOT(nextAnimationFrame()));
	animationTimer->start(ANIMATION_FRAME_LENGTH);
}

void GLApplicationController::canvasWidgetChanged()
{
	window->resetInterface();
}

void GLApplicationController::xRotSliderChanged(int newValue)
{
	drawable->setXRotation( static_cast<float>(newValue) );
	window->resetInterface();
}

void GLApplicationController::yRotSliderChanged(int newValue)
{
	drawable->setYRotation( static_cast<float>(newValue) );
	window->resetInterface();
}

void GLApplicationController::zRotSliderChanged(int newValue)
{
	drawable->setZRotation( static_cast<float>(newValue) );
	window->resetInterface();
}

void GLApplicationController::animationCheckBoxChanged(int newState)
{
	animating = (newState == Qt::Checked);
}

void GLApplicationController::skeletalAnimationCheckBoxChanged(int newState)
{
    skeletalAnimationPlaying = (newState == Qt::Checked);
}

void GLApplicationController::nextAnimationFrame()
{
	if (animating) // if Y-rotation animation is playing
	{
		Vector3 rotation = drawable->rotation();
		if (rotation.y < 0.0f || rotation.y > 360.0f) rotation.y = 0.0f;
		else rotation.y += 1.0f;
		drawable->setRotation(rotation);
	}
	if (skeletalAnimationPlaying) // if skeletal animations are playing
	{
	    // TOOD
    }
	// If ANY animation is playing, update the animation
	if (animating || skeletalAnimationPlaying)
		window->resetInterface();
}

