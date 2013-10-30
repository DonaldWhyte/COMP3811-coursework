#include <QApplication>
#include "GLWindow.h"
#include "GLApplicationController.h"

#include "animation/Skeleton.h"
#include "surfaces/SurfaceFactory.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	// Construct skeleton to draw (model)
	SurfaceFactory surfaceFactory;
	Surface cylinder = surfaceFactory.createCylinder(0.5f, 0.5f, 16);
	Bone rootBone(&cylinder);
	Drawable* drawable = new Skeleton(&rootBone);

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
