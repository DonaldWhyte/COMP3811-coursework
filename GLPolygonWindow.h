#ifndef GL_POLYGON_WINDOW_H
#define GL_POLYGON_WINDOW_H

#include <QLabel>
#include <QMenuBar>
#include <QSlider>
#include <QDial>
#include <QCheckBox>
#include <QBoxLayout>
#include "GLPolygon.h"
#include "GLPolygonWidget.h"

/* Main window for application. */
class GLPolygonWindow : public QWidget
{

	Q_OBJECT

public:
	GLPolygonWindow(QWidget* parent, GLPolygon* initialPolygon);
	virtual ~GLPolygonWindow();

	void setPolygon(GLPolygon* newPolygon);
	/* Called when the state of the model changes. Ensures all
 	 * widgets' states reflect the model's state and everything
 	 * is redrawn to the user. */
	void resetInterface();

	/* These widgets are public so signals produced by
         * them can be handled by the controller. */
	GLPolygonWidget* polygonWidget;

	QSlider* nVerticesSlider;
	QSlider* xSlider;
	QSlider* ySlider;
	QDial* rotationDial;
	QCheckBox* animationCheckBox;

	QAction* actionQuit;

private:
	GLPolygon* polygon;

	// Visual hierarchy
	QMenuBar* menuBar;
		QMenu* fileMenu;
	QBoxLayout* windowLayout;
		QBoxLayout* rowOneLayout;
			QBoxLayout* ySliderLayout;
				QLabel* yLabel;
		QBoxLayout* rowTwoLayout;
			QLabel* xLabel;
		QBoxLayout* rowThreeLayout;
			QLabel* numVerticesLabel;

};

#endif
