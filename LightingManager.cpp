#include "LightingManager.h"
#include <QGLWidget> // for OpenGL functions

const float LightingManager::LIGHT_POSITION[4] = { 0.5f, 0.0f, 0.0f, 1.0f };
const float LightingManager::AMBIENT_COLOUR[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
const float LightingManager::DIFFUSE_COLOUR[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
const float LightingManager::SPECULAR_COLOUR[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

LightingManager::LightingManager()
{
	setLightingModel(LIGHTING_MODEL_NONE);
	setupLights();
}

LightingModel LightingManager::lightingModel() const
{
	return lModel;
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
		glEnable(GL_COLOR_MATERIAL);
	}
	else
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
	}	
}

void LightingManager::setupLights()
{
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AMBIENT_COLOUR);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DIFFUSE_COLOUR);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SPECULAR_COLOUR);
}
