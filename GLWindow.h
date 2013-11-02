#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <QLabel>
#include <QMenuBar>
#include <QSlider>
#include <QDial>
#include <QCheckBox>
#include <QRadioButton>
#include <QBoxLayout>
#include <QComboBox>
#include "Drawable.h"
#include "animation/Animator.h"
#include "GLCanvasWidget.h"

/* Main window for application. */
class GLWindow : public QWidget
{

	Q_OBJECT

public:
	GLWindow(QWidget* parent, Drawable* drawableObject, Animator* animator);
	virtual ~GLWindow();

	void setDrawable(Drawable* newDrawable);
	void setAnimator(Animator* newAnimator);	

	/* Called when the state of the model changes. Ensures all
 	 * widgets' states reflect the model's state and everything
 	 * is redrawn to the user. */
	void resetInterface();

	/* These widgets are public so signals produced by
         * them can be handled by the controller. */
	GLCanvasWidget* canvasWidget;

	QSlider* xRotSlider;
	QSlider* yRotSlider;
	QSlider* zRotSlider;
	QSlider* animationSlider;
	QCheckBox* animationCheckBox;
	QCheckBox* skeletalAnimationCheckBox;

	QAction* actionQuit;

private:
	Drawable* drawable;
	Animator* animator;

	// Visual hierarchy
	QMenuBar* menuBar;
		QMenu* fileMenu;
	QBoxLayout* windowLayout;
		QBoxLayout* rowOneLayout;
		QBoxLayout* rowTwoLayout;
			QLabel* xRotLabel;
		QBoxLayout* rowThreeLayout;
			QLabel* yRotLabel;
		QBoxLayout* rowFourLayout;
			QLabel* zRotLabel;
		QBoxLayout* rowFiveLayout;
		QBoxLayout* rowSixLayout;
		    QLabel* animationLabel;

};

#endif
