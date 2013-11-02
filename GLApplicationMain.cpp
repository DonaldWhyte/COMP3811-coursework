#include <QApplication>
#include "GLWindow.h"
#include "GLApplicationController.h"

#include "animation/Skeleton.h"
#include "animation/Axes.h"
#include "animation/Person.h"
#include "surfaces/SurfaceFactory.h"
#include "CompositeDrawable.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

    CompositeDrawable* compositeDrawable = new CompositeDrawable();
    compositeDrawable->setZ(-30.0f); // so everything is visible
    // Create axes
    Bone* axes = Axes::createXYZAxes(7.5f, 0.5f);
    compositeDrawable->addDrawable(new Skeleton(axes));
    // Create a person using bone transformations
    SurfaceFactory surfaceFactory(false, false, true);
    Person* person = new Person(&surfaceFactory);
    compositeDrawable->addDrawable(person);
    // Add animated objects to a special list the controller
    // can use to keep the animations updated
    std::vector<Bone*> animatedObjects;
    animatedObjects.push_back(person->getRootBone());

	// Now build view and controller
	GLWindow* window = new GLWindow(NULL, compositeDrawable);
	GLApplicationController* controller = new GLApplicationController(
	    window, compositeDrawable, animatedObjects);

	window->resize(1280, 1280);
	window->show();

	app.exec();

	delete controller;
	delete window;
	delete compositeDrawable;

	return 0;
}
