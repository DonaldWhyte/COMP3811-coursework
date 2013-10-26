#include <QCoreApplication>
#include "GLApplicationController.h"

#include <typeinfo>
#include "Sphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Torus.h"

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
	connect(window->geometryTypeChooser, SIGNAL(currentIndexChanged(int)),
		this, SLOT(geometryTypeChooserIndexChanged(int)));
	connect(window->detailSlider, SIGNAL(valueChanged(int)),
		this, SLOT(detailSliderChanged(int)));

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
	// We keep the old drawable around so we pass some of its state to the new drawable
	Drawable* oldDrawable = drawable;
	// Also get the level of detail required from another widget
	int detail = window->detailSlider->value();

	switch (newIndex)
	{
	case 0: // Sphere
		drawable = new Sphere(0.5f, detail, detail);
		break;
	case 1: // Cylinder
		drawable = new Cylinder(0.75f, 0.5f, detail);
		break;
	case 2: // Cone
		drawable = new Cone(0.75f, 0.5f, detail);
		break;
	case 3: // Torus
		drawable = new Torus(0.25f, 0.5f, detail, detail);
		break;
	default: // if default case, just do nothing and leave current object - RETURN AND STOP FUNCTION!
		return;
	}
	// Restore drawable transformations
	drawable->setPosition(oldDrawable->position());
	drawable->setRotation(oldDrawable->rotation());
	// Restore old render method and colouring (if instance is a mesh)
	drawable->setRenderMethod(oldDrawable->renderMethod());
	Mesh* oldMesh = dynamic_cast<Mesh*>(oldDrawable);
	Mesh* meshObject = dynamic_cast<Mesh*>(drawable);
	if (oldMesh && meshObject)
	{
		meshObject->setColouring(oldMesh->colouring());
		meshObject->setGeometryType(oldMesh->geometryType());
		meshObject->showNormals(oldMesh->showingNormals());
	}

	window->setDrawable(drawable);
	window->resetInterface();

	delete oldDrawable;
}

void GLApplicationController::colourChooserIndexChanged(int newIndex)
{
	// If object is an instance of mesh, assign new colouring
	Mesh* meshObject = dynamic_cast<Mesh*>(drawable);
	if (meshObject)
	{
		Mesh::Colouring newColouring = static_cast<Mesh::Colouring>(newIndex);
		meshObject->setColouring(newColouring);
		if (newColouring == Mesh::MESH_FLAT_SHADING)
			meshObject->setPerFaceNormals(true);
		else
			meshObject->setPerFaceNormals(false);
	}
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

void GLApplicationController::detailSliderChanged(int newValue)
{
	objectChooserIndexChanged( window->objectChooser->currentIndex() );
	window->resetInterface();
}

void GLApplicationController::nextAnimationFrame()
{
	if (!animating) return;

	Vector3 rotation = drawable->rotation();
	if (rotation.y < 0.0f || rotation.y > 360.0f) rotation.y = 0.0f;
	else rotation.y += 1.0f;
	drawable->setRotation(rotation);

	window->resetInterface();
}

void GLApplicationController::geometryTypeChooserIndexChanged(int newIndex)
{
	Mesh* meshObject = dynamic_cast<Mesh*>(drawable);
	if (meshObject)
	{
		meshObject->setGeometryType( static_cast<Mesh::GeometryType>(newIndex) );
	}

	window->resetInterface();
}

