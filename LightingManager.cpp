#include "LightingManager.h"
#include <QGLWidget> // for OpenGL functions

const float LightingManager::LIGHT_POSITION[4] = { -100, 100, 0, 1 };
const float LightingManager::AMBIENT_COLOUR[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
const float LightingManager::DIFFUSE_COLOUR[4] = { 2.0f, 2.0f, 2.0f, 1.0f };
const float LightingManager::SPECULAR_COLOUR[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

LightingManager::LightingManager() : lModel(LIGHTING_MODEL_NONE)
{
}

LightingModel LightingManager::lightingModel() const
{
	return lModel;
}

void LightingManager::initialise()
{
	setLightingModel(LIGHTING_MODEL_NONE);
	setupLights();
}

void LightingManager::setLightingModel(LightingModel newModel) 
{
	lModel = newModel;
	// Changes OpenGL state to reflect the model change
	updateGLState();
}

void LightingManager::updateGLState()
{
	switch (lModel)
	{
	case LIGHTING_MODEL_NONE:
		enableLighting(false);
		break;
	case LIGHTING_MODEL_FLAT:
		enableLighting(true);
		glShadeModel(GL_FLAT);
		break;
	case LIGHTING_MODEL_SMOOTH:
		enableLighting(true);
		glShadeModel(GL_SMOOTH);
		break;
	}
}

void LightingManager::enableLighting(bool enabled)
{
	if (enabled)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}
}

void LightingManager::setupLights()
{
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AMBIENT_COLOUR);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DIFFUSE_COLOUR);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SPECULAR_COLOUR);
}
