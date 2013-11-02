#ifndef GL_APPLICATION_CONTROLLER_H
#define GL_APPLICATION_CONTROLLER_H

#include <QTimer>
#include "GLWindow.h"
#include "Drawable.h"
#include "animation/Animator.h"

/* Controller for main program. */
class GLApplicationController : public QObject
{

	Q_OBJECT

public:
	GLApplicationController(GLWindow* window, Drawable* drawableObject,
		Animator* animator);

public slots:
	void canvasWidgetChanged();
	void xRotSliderChanged(int newValue);
	void yRotSliderChanged(int newValue);
	void zRotSliderChanged(int newValue);
	void animationSliderChanged(int newValue);
	void skeletalAnimationCheckBoxChanged(int state);
	void nextAnimationFrame(); // used to provide animation to objects 

private:
	// Length of each frame for polygon animation. This is in milliseconds
	static const double ANIMATION_FRAME_LENGTH = 16.67;

	GLWindow* window;
	Drawable* drawable;
	// used to animate the scene
    Animator* animator;
	QTimer* animationTimer;

	// Ifset to true, then the skeletal animation of the person will be playing
	bool skeletalAnimationPlaying;
	// If set to true, triangles composing the faces of polyhedra
	// will be coloured differently
	bool colourTriangles;

};

#endif
