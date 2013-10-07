#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <QLabel>
#include <QMenuBar>
#include <QSlider>
#include <QDial>
#include <QCheckBox>
#include <QRadioButton>
#include <QBoxLayout>
#include "Drawable.h"
#include "GLCanvasWidget.h"

/* Main window for application. */
class GLWindow : public QWidget
{

	Q_OBJECT

public:
	GLWindow(QWidget* parent, Drawable* drawableObject);
	virtual ~GLWindow();

	void setDrawable(Drawable* newDrawable);

	/* Called when the state of the model changes. Ensures all
 	 * widgets' states reflect the model's state and everything
 	 * is redrawn to the user. */
	void resetInterface();

	/* These widgets are public so signals produced by
         * them can be handled by the controller. */
	GLCanvasWidget* canvasWidget;

	QSlider* xSlider;
	QSlider* ySlider;
	QDial* rotationDial;
	QCheckBox* animationCheckBox;

	QRadioButton* pointRadio;
	QRadioButton* lineRadio;
	QRadioButton* triangleRadio;

	QCheckBox* colourTrianglesCheckBox;

	QAction* actionQuit;

private:
	Drawable* drawable;

	// Visua hierarchy
	QMenuBar* menuBar;
		QMenu* fileMenu;
	QBoxLayout* windowLayout;
		QBoxLayout* rowOneLayout;
			QBoxLayout* ySliderLayout;
				QLabel* yLabel;
		QBoxLayout* rowTwoLayout;
			QLabel* xLabel;
			QBoxLayout* rotationLayout;
		QBoxLayout* rowThreeLayout;
			QLabel* renderModeLabel;
		QBoxLayout* rowFourLayout;

};

#endif
