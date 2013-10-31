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

Bone* createArm(SurfaceFactory* surfaceFactory, Vector3 rootPosition, Vector3 rootOrientation, bool reverseDirection)
{
    float armDirection = 10.0f;
    Vector3 upperArmPosition(0.15f, -0.7f, 0.0f);    
    Vector3 lowerArmPosition(-0.14f, 0.0f, 0.8f);     
    if (reverseDirection)
    {
        armDirection = -armDirection;
        upperArmPosition.x = -upperArmPosition.x;
        lowerArmPosition.x = -lowerArmPosition.x;
    }
   
    Surface* shoulderJoint = surfaceFactory->createSphere(0.4f, 32, 32);
    Surface* upperArmComponent = surfaceFactory->createCylinder(2.0f, 0.25f, 32);
    Surface* elbowJoint = surfaceFactory->createSphere(0.3f, 32, 32);
    Surface* lowerArmComponent = surfaceFactory->createCylinder(1.4f, 0.25f, 32);    
        
    Bone* shoulder = new Bone(shoulderJoint, rootPosition, rootOrientation);
    Bone* upperArm = new Bone(upperArmComponent, upperArmPosition, Vector3(90.0f, armDirection, 0.0f));
    shoulder->addChild(upperArm);
    Bone* elbow = new Bone(elbowJoint, Vector3(0.0f, 0.0f, 1.1f), Vector3(0, 0, 0));
    upperArm->addChild(elbow);    
    Bone* lowerArm = new Bone(lowerArmComponent, lowerArmPosition, Vector3(0, -armDirection, 0));
    elbow->addChild(lowerArm);
    Bone* hand = new Bone(elbowJoint, Vector3(0, 0, 0.9f), Vector3(0, 0, 0));
    lowerArm->addChild(hand);
    return shoulder;
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
    Bone* leftArm = createArm(&surfaceFactory,
        Vector3(-0.2f, 1.9f, 0.55f), Vector3(0.0f, 0.0f, 0.0f), true);
    Bone* rightArm = createArm(&surfaceFactory,
        Vector3(2.2f, 1.9f, 0.55f), Vector3(0.0f, 0.0f, 0.0f), false);
    chestBone->addChild(leftArm);        
    chestBone->addChild(rightArm);
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

	window->resize(1280, 1280);
	window->show();

	app.exec();

	delete controller;
	delete window;
	delete compositeDrawable;
	delete axes;
    delete pelvisBone; // root of person

	return 0;
}
