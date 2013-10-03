#include "GLPolygonWindow.h"

GLPolygonWindow::GLPolygonWindow(QWidget* parent, GLPolygon* initialPolygon)
	: QWidget(parent), polygon(initialPolygon)
{
	setWindowTitle("COMP3811 Computer Graphics - Coursework One - Donald Whyte");
	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	// Menu bar
	menuBar = new QMenuBar(this);
	fileMenu = menuBar->addMenu("&File");
	actionQuit = new QAction("&Quit", this);
	fileMenu->addAction(actionQuit);

	// Row one, which contains OpenGL widget and verticval slider
	rowOneLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowOneLayout);

	polygonWidget = new GLPolygonWidget(this, initialPolygon);
	rowOneLayout->addWidget(polygonWidget);

	ySliderLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	rowOneLayout->addLayout(ySliderLayout);
		yLabel = new QLabel("Y");
		ySliderLayout->addWidget(yLabel);
		ySlider = new QSlider(Qt::Vertical);
		ySliderLayout->addWidget(ySlider);

	// Row two, which contains horizontal slider and rotation dial
	rowTwoLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowTwoLayout);

	xLabel = new QLabel("X");
	rowTwoLayout->addWidget(xLabel);

	xSlider = new QSlider(Qt::Horizontal);
	rowTwoLayout->addWidget(xSlider);

	rotationDial = new QDial();
	rowTwoLayout->addWidget(rotationDial);

	// Row three, which contains number of vertices slider and animation checkbox
	rowThreeLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowThreeLayout);

	numVerticesLabel = new QLabel("# Vertices");
	rowThreeLayout->addWidget(numVerticesLabel);

	nVerticesSlider = new QSlider(Qt::Horizontal);
	rowThreeLayout->addWidget(nVerticesSlider);

	animationCheckBox = new QCheckBox("Animate Polygon");
	rowThreeLayout->addWidget(animationCheckBox);

	resetInterface();
}

GLPolygonWindow::~GLPolygonWindow()
{
	// Done in reverse-order, bottom of visual hierarchy to the top
	delete yLabel;
	delete ySlider;
	delete xLabel;
	delete numVerticesLabel;
	delete animationCheckBox;
	delete rotationDial;
	delete xSlider;
	delete ySliderLayout;
	delete nVerticesSlider;
	delete polygonWidget;
	delete rowOneLayout;
	delete rowTwoLayout;
	delete rowThreeLayout;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
}

void GLPolygonWindow::setPolygon(GLPolygon* newPolygon)
{
	polygon = newPolygon;
}

void GLPolygonWindow::resetInterface()
{
	nVerticesSlider->setMinimum(3);
	nVerticesSlider->setMaximum(30);
	nVerticesSlider->setValue(polygon->numVertices());

	xSlider->setMinimum(-100);
	xSlider->setMaximum(100);
	xSlider->setValue( static_cast<int>(polygon->x() * 100.0f) );
	ySlider->setMinimum(-100);
	ySlider->setMaximum(100);
	ySlider->setValue( static_cast<int>(polygon->y() * 100.0f) );

	rotationDial->setMinimum(0);
	rotationDial->setMaximum(360);
	rotationDial->setValue(polygon->rotationDegrees());

	update(); // force refresh
	polygonWidget->update(); // wasn't repainting with update()...
}


