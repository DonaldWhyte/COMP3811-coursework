#include <QApplication>
#include "GLWindow.h"
#include "GLApplicationController.h"

#include "animation/Skeleton.h"
#include "animation/Axes.h"
#include "surfaces/SurfaceFactory.h"
#include "CompositeDrawable.h"

Bone* createLeg(SurfaceFactory* surfaceFactory, Vector3 rootPosition, Vector3 rootOrientation)
{
    Surface* joint = surfaceFactory->createSphere(0.4f, 32, 32);    
    Surface* legComponent = surfaceFactory->createCylinder(1.6f, 0.3f, 32);
    Surface* foot = surfaceFactory->createBox(0.7f, 1.1f, 0.5f);
    Bone* thigh = new Bone(legComponent, rootPosition, rootOrientation);
    Bone* knee = new Bone(joint, Vector3(0, 0, 1.0f));
    thigh->addChild(knee);
    Bone* shin = new Bone(legComponent, Vector3(0.0f, 0.0f, 1.0f));
    knee->addChild(shin);    
    Bone* leg = new Bone(foot, Vector3(-0.35f, -0.35f, 0.8f));
    shin->addChild(leg);
    
    return thigh;
}

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
    // Create person's left and right arms
    // TODO
    // Create person's left and right legs
    Bone* leftLeg = createLeg(&surfaceFactory,
        Vector3(0.5f, -0.8f, 0.55f), Vector3(90.0f, 0.0f, 0.0f));
    Bone* rightLeg = createLeg(&surfaceFactory,
        Vector3(1.5f, -0.8f, 0.55f), Vector3(90.0f, 0.0f, 0.0f));        
    pelvisBone->addChild(leftLeg);
    pelvisBone->addChild(rightLeg);
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
