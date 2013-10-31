#include <QApplication>
#include "GLWindow.h"
#include "GLApplicationController.h"

#include "animation/Skeleton.h"
#include "animation/Axes.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	// Construct skeleton to draw bones
	Bone* axes = Axes::createXYZAxes(7.5f, 0.5f);
	Drawable* drawable = new Skeleton(axes);
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
	delete axes;

	return 0;
}
