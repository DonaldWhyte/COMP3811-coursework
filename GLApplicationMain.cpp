#include <QApplication>
#include "GLWindow.h"
#include "GLApplicationController.h"

#include "Cube.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	GLPlatonicSolid* drawable = new Cube();
	drawable->setRenderMethod(RENDER_METHOD_LINES);
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
