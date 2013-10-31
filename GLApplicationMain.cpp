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
    compositeDrawable->addDrawable( new Skeleton(axes) );
    // Create sphere
	SurfaceFactory surfaceFactory;
	Surface* sphere = surfaceFactory.createSphere(3.0f, 32, 32);
	sphere->setShowPoints(true);		    
	Bone* sphereBone = new Bone(sphere);    
    compositeDrawable->addDrawable( new Skeleton(sphereBone) );

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

	return 0;
}
