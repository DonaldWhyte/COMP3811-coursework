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
	Surface cylinder = surfaceFactory.createCone(0.75f, 0.25f, 8);
	Bone rootBone(&cylinder);

	Drawable* drawable = new Skeleton(&rootBone);
	drawable->setZ(-2.5f); // so drawable is visible

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
