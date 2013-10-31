#include <QApplication>
#include "GLWindow.h"
#include "GLApplicationController.h"

#include "animation/Skeleton.h"
#include "surfaces/SurfaceFactory.h"
#include "Cylinder.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	// Construct skeleton to draw (model)
	SurfaceFactory surfaceFactory;
	Surface cylinder = surfaceFactory.createCylinder(7.5f, 0.1f, 32);
	Surface cone = surfaceFactory.createCone(0.75f, 0.1f, 32);	
	Bone rootBone(NULL);
	rootBone.addChild( new Bone(&cylinder, Vector3(0, 0, 0), Vector3(0, 0, 0)) );
	rootBone.addChild( new Bone(&cylinder, Vector3(0, 0, 0), Vector3(0, 90, 0)) );
	rootBone.addChild( new Bone(&cylinder, Vector3(0, 0, 0), Vector3(90, 0, 0)) );

	Drawable* drawable = new Skeleton(&rootBone);
	drawable->setZ(-10.0f); // so drawable is visible

	// Now build view and controller
	GLWindow* window = new GLWindow(NULL, drawable);
	GLApplicationController* controller = new GLApplicationController(window, drawable);

	window->resize(640, 640);
	window->show();

	app.exec();

	delete controller;
	delete window;
	delete drawable;

	return 0;
}
