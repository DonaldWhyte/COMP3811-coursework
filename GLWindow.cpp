#include "GLWindow.h"

GLWindow::GLWindow(QWidget* parent, Drawable* drawableObject)
	: QWidget(parent), drawable(drawableObject)
{
	setWindowTitle("COMP3811 Computer Graphics - Coursework Four - Donald Whyte");
	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	// Menu bar
	menuBar = new QMenuBar(this);
	fileMenu = menuBar->addMenu("&File");
	actionQuit = new QAction("&Quit", this);
	fileMenu->addAction(actionQuit);

	// Row one, which contains OpenGL widget and vertical slider
	rowOneLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowOneLayout);

	canvasWidget = new GLCanvasWidget(this, drawableObject);
	rowOneLayout->addWidget(canvasWidget);

	rowTwoLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowTwoLayout);
		xRotLabel = new QLabel("X Rotation");
		rowTwoLayout->addWidget(xRotLabel);
		xRotSlider = new QSlider(Qt::Horizontal);
		rowTwoLayout->addWidget(xRotSlider);

	rowThreeLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowThreeLayout);
		yRotLabel = new QLabel("Y Rotation");
		rowThreeLayout->addWidget(yRotLabel);
		yRotSlider = new QSlider(Qt::Horizontal);
		rowThreeLayout->addWidget(yRotSlider);

	rowFourLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowFourLayout);
		zRotLabel = new QLabel("Z Rotation");
		rowFourLayout->addWidget(zRotLabel);
		zRotSlider = new QSlider(Qt::Horizontal);
		rowFourLayout->addWidget(zRotSlider);

	rowFiveLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowFiveLayout);
		animationCheckBox = new QCheckBox("Y Rotation Animation Enabled");
		rowFiveLayout->addWidget(animationCheckBox);
		skeletalAnimationCheckBox = new QCheckBox("Skeletal Animation Enabled");
		rowFiveLayout->addWidget(skeletalAnimationCheckBox);

    resetInterface();
}

GLWindow::~GLWindow()
{
	// Done in reverse-order, bottom of visual hierarchy to the top
	delete skeletalAnimationCheckBox;
	delete animationCheckBox;
	delete xRotLabel;
	delete yRotLabel;
	delete zRotLabel;
	delete xRotSlider;
	delete yRotSlider;
	delete zRotSlider;
	delete canvasWidget;
	delete rowOneLayout;
	delete rowTwoLayout;
	delete rowThreeLayout;
	delete rowFourLayout;
	delete rowFiveLayout;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
}

void GLWindow::setDrawable(Drawable* newDrawable)
{
	drawable = newDrawable;
	// Also make sure the canvas widget knows about
	// the new drawable so it can be rendered
	canvasWidget->setDrawable(newDrawable);
}

void GLWindow::resetInterface()
{
	xRotSlider->setMinimum(0);
	xRotSlider->setMaximum(360);
	xRotSlider->setValue(drawable->xRotation());
	yRotSlider->setMinimum(0);
	yRotSlider->setMaximum(360);
	yRotSlider->setValue(drawable->yRotation());
	zRotSlider->setMinimum(0);
	zRotSlider->setMaximum(360);
	zRotSlider->setValue(drawable->zRotation());

	update(); // force refresh
	canvasWidget->update(); // wasn't repainting with update()...
}
