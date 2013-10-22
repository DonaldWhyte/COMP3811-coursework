#ifndef GL_LIGHTING_MANAGER_H
#define GL_LIGHTING_MANAGER_H

enum LightingModel
{
	LIGHTING_MODEL_NONE = 0,
	LIGHTING_MODEL_FLAT,
	LIGHTING_MODEL_SMOOTH
};

class LightingManager
{

public:
	LightingManager();
	void initialise();

	LightingModel lightingModel() const;
	void setLightingModel(LightingModel newModel);

private:
	static const float LIGHT_POSITION[];
	static const float AMBIENT_COLOUR[];
	static const float DIFFUSE_COLOUR[];
	static const float SPECULAR_COLOUR[];

	void setupLights();
	void enableLighting(bool enabled);
	void updateGLState();

	LightingModel lModel;

};

#endif
