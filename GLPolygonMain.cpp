#include <QApplication>
#include "GLPolygonWindow.h"
#include "GLPolygonController.h"
#include "GLPolygon.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	GLPolygon* polygon = new GLPolygon();
	GLPolygonWindow* window = new GLPolygonWindow(NULL, polygon);
	GLPolygonController* controller = new GLPolygonController(window, polygon);

	window->resize(512, 512);
	window->show();

	app.exec();

	delete controller;
	delete window;
	delete polygon;

	return 0;
}
