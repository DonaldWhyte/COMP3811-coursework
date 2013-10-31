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
    compositeDrawable->setZ(-20.0f); // so everything is visible
    // Create axes
    Bone* axes = Axes::createXYZAxes(7.5f, 0.5f);
    compositeDrawable->addDrawable(new Skeleton(axes));
    
    // Create a person using bone transformations
    SurfaceFactory surfaceFactory(false, false, true);
    // Create person's body
    Bone* pelvisBone = new Bone(surfaceFactory.createBox(2.0f, 1.8f, 1.1f));
    Bone* chestBone = new Bone(surfaceFactory.createBox(2.0f, 2.2f, 1.1f),
        Vector3(0.0f, 1.8f, 0.0f));
    pelvisBone->addChild(chestBone);
    // Create person's head (and neck)
   Bone* neckBone = new Bone(surfaceFactory.createCylinder(0.3f, 0.5f, 32),
        Vector3(1.0f, 2.2f, 0.5f), Vector3(90.0f, 0.0f, 0.0f));
    chestBone->addChild(neckBone);
    Bone* headBone = new Bone(surfaceFactory.createSphere(0.9f, 32, 32),
        Vector3(0.0f, 0.0f, -0.7f));
    neckBone->addChild(headBone);    
        
 
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
