#include <QApplication>
#include "GLWindow.h"
#include "GLApplicationController.h"

#include "GLPlatonicSolid.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	GLPlatonicSolid* drawable = new GLPlatonicSolid(PLATONIC_CUBE, RENDER_METHOD_TRIANGLES);
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
