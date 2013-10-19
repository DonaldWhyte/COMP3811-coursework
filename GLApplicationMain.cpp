#include <QApplication>
#include "GLWindow.h"
#include "GLApplicationController.h"

#include "Sphere.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Drawable* drawable = new Sphere(0.25f, 10, 10);
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
