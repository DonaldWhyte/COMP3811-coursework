#include <QCoreApplication>
#include "GLApplicationController.h"

GLApplicationController::GLApplicationController(GLWindow* window, Drawable* drawableObject,
    Animator* animator)
	: window(window), drawable(drawableObject), animator(animator), skeletalAnimationPlaying(true)
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
	connect(window->animationSlider, SIGNAL(valueChanged(int)),
		this, SLOT(animationSliderChanged(int)));
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

void GLApplicationController::animationSliderChanged(int newValue)
{
	animator->setCurrentFrame(newValue);
	window->resetInterface();
}

void GLApplicationController::skeletalAnimationCheckBoxChanged(int newState)
{
    skeletalAnimationPlaying = (newState == Qt::Checked);
}

void GLApplicationController::nextAnimationFrame()
{
	if (skeletalAnimationPlaying)
	{	
        animator->update();
        window->resetInterface();
    }
		
}

