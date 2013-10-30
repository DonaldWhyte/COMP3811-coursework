#include <QApplication>
#include "GLWindow.h"
#include "GLApplicationController.h"

#include "animation/Skeleton.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	// Construct skeleton to draw (model)
	Bone rootBone(NULL);
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
