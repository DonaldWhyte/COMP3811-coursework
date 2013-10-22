#include <QCoreApplication>
#include "GLApplicationController.h"

#include <typeinfo>
#include "GLPlatonicSolid.h"
#include "Sphere.h"
//#include "Cylinder.h"
//#include "Cone.h"
//#include "Torus.h"

GLApplicationController::GLApplicationController(GLWindow* window, Drawable* drawableObject)
	: window(window), drawable(drawableObject), animating(false)
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

	connect(window->objectChooser, SIGNAL(currentIndexChanged(int)),
		this, SLOT(objectChooserIndexChanged(int)));
	connect(window->colourChooser, SIGNAL(currentIndexChanged(int)),
		this, SLOT(colourChooserIndexChanged(int)));

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

void GLApplicationController::objectChooserIndexChanged(int newIndex)
{
	// We keep the drawable's current rendering method so
	// we can restore if it a new drawable is created
	RenderMethod oldRenderMethod = drawable->renderMethod();

	switch (newIndex)
	{
	case 0: // Sphere
		drawable = new Sphere(0.5, 10, 10);
		break;
	case 1: // Cylinder
		//drawable = new Cylinder();
		break;
	case 2: // Cone
		//drawable = new Cone();
		break;
	case 3: // Torus
		//drawable = new Torus();
		break;
	default: // if default case, just do nothing and leave current object
		return;
	}
	// Restore old render method and colouring (if instance is a mesh)
	drawable->setRenderMethod(oldRenderMethod);
	Mesh* meshObject = dynamic_cast<Mesh*>(drawable);
	if (meshObject)
		meshObject->setColouring( static_cast<Mesh::Colouring>(newIndex) );

	window->setDrawable(drawable);
	window->resetInterface();
}

#include <iostream>
void GLApplicationController::colourChooserIndexChanged(int newIndex)
{
	// If object is an instance of mesh, assign new colouring
	Mesh* meshObject = dynamic_cast<Mesh*>(drawable);
	if (meshObject)
		meshObject->setColouring( static_cast<Mesh::Colouring>(newIndex) );
	// Depending on colourig, change lighting parameers
	LightingModel lightingModel = LIGHTING_MODEL_NONE;
	switch (newIndex)
	{
	case 2: // flat shading
		lightingModel = LIGHTING_MODEL_FLAT;
		break;
	case 3: // smooth shading
	case 4:
		lightingModel = LIGHTING_MODEL_SMOOTH;
		break;
	}
	window->canvasWidget->setLightingModel(lightingModel);

	window->resetInterface();
}

void GLApplicationController::nextAnimationFrame()
{
	if (!animating) return;

	Vector3 rotation = drawable->rotation();
	if (rotation.x < 0.0f || rotation.x > 360.0f) rotation.x = 0.0f;
	else rotation.x += 1.0f;
	if (rotation.y < 0.0f || rotation.y > 360.0f) rotation.y = 0.0f;
	else rotation.y += 1.0f;
	if (rotation.z < 0.0f || rotation.z > 360.0f) rotation.z = 0.0f;
	else rotation.z += 1.0f;
	drawable->setRotation(rotation);

	window->resetInterface();
}
