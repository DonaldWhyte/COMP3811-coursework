#include <QApplication>
#include "GLWindow.h"
#include "GLApplicationController.h"

#include "animation/Skeleton.h"
#include "animation/Axes.h"
#include "surfaces/SurfaceFactory.h"
#include "CompositeDrawable.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

    CompositeDrawable* compositeDrawable = new CompositeDrawable();
    compositeDrawable->setZ(-10.0f); // so everything is visible
    // Create axes
    Bone* axes = Axes::createXYZAxes(7.5f, 0.5f);
    compositeDrawable->addDrawable(new Skeleton(axes));
    
    // Create a person using bone transformations
    SurfaceFactory surfaceFactory(true);
    // Create person's body
    Bone* pelvisBone = new Bone(surfaceFactory.createBox(0.75f, 1.0f, 0.5f));
    Bone* chestBone = new Bone(surfaceFactory.createBox(0.75f, 2.0f, 0.5f),
        Vector3(0.0f, 1.0f, 0.0f));
    pelvisBone->addChild(chestBone);
    // Create person's head
    // TODO
    // Create person's left arm
    // TODO
    // Create person's right arm
    // TODO
    // Create person's left leg
    // TODO
    // Create person's right leg
    // TODO
    // Add the person to the composite to render them
    compositeDrawable->addDrawable( new Skeleton(pelvisBone) );

	// Now build view and controller
	GLWindow* window = new GLWindow(NULL, compositeDrawable);
	GLApplicationController* controller = new GLApplicationController(window, compositeDrawable);

	window->resize(640, 640);
	window->show();

	app.exec();

	delete controller;
	delete window;
	delete compositeDrawable;
	delete axes;
    delete pelvisBone; // root of person

	return 0;
}
