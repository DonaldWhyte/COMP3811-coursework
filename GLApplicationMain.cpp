#include <QApplication>
#include "GLWindow.h"
#include "GLApplicationController.h"

#include "animation/Skeleton.h"
#include "animation/Axes.h"
#include "animation/Person.h"
#include "animation/Animator.h"
#include "surfaces/SurfaceFactory.h"
#include "CompositeDrawable.h"

int main(int argc, char* argv[])
{
    // Create application and window BEFORE drawables, so an OpenGL
    // context has been established and textures can be correctly loaded
	QApplication app(argc, argv);
	
	// Built objects that will be drawn on the screen
    CompositeDrawable* compositeDrawable = new CompositeDrawable();
    compositeDrawable->setZ(-30.0f); // so everything is visible
    // Create axes
    Bone* axes = Axes::createXYZAxes(15.0f, 0.5f);
    compositeDrawable->addDrawable(new Skeleton(axes));
    // Create a person using bone transformations
    SurfaceFactory surfaceFactory(false, false, true);
    Person* person = new Person(&surfaceFactory);
    compositeDrawable->addDrawable(person);
    // Add animated objects to a special list the controller
    // can use to keep the animations updated
    Animator animator(person->getRootBone()->totalFrames(), person->getRootBone());

	// Create view and controller
	GLWindow* window = new GLWindow(NULL, compositeDrawable, &animator);
	GLApplicationController* controller = new GLApplicationController(
	    window, compositeDrawable, &animator);

	window->resize(1280, 1280);
	window->show();

	app.exec();

	delete controller;
	delete window;
	delete compositeDrawable;

	return 0;
}
