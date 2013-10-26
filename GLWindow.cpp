#include "GLWindow.h"

static const int INITIAL_OBJECT_INDEX = 0;
static const int INITIAL_COLOUR_INDEX = 0;
static const int INITIAL_GEOMTYPE_INDEX = 2;

GLWindow::GLWindow(QWidget* parent, Drawable* drawableObject)
	: QWidget(parent), drawable(drawableObject)
{
	// Define list of drawable objects
	QStringList objectNameList;
	objectNameList << "Sphere" << "Cylinder" << "Cone" << "Torus";
	QStringList colourNameList;
	colourNameList << "Same" << "Alternate Colours" << "Flat Shading" << "Smooth Shading" << "Texture";
	QStringList geometryTypeList;
	geometryTypeList << "Points" << "Lines" << "Triangles";

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

	rowSixLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowSixLayout);
		objectChooserLabel = new QLabel("Object");
		rowSixLayout->addWidget(objectChooserLabel);
		objectChooser = new QComboBox();
		objectChooser->addItems(objectNameList);
		objectChooser->setCurrentIndex(INITIAL_OBJECT_INDEX);
		rowSixLayout->addWidget(objectChooser);

	rowSevenLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowSevenLayout);
		colourLabel = new QLabel("Triangle Colouring");
		rowSevenLayout->addWidget(colourLabel);
		colourChooser = new QComboBox();
		colourChooser->addItems(colourNameList);
		colourChooser->setCurrentIndex(INITIAL_COLOUR_INDEX);
		rowSevenLayout->addWidget(colourChooser);

	rowEightLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowEightLayout);
		geometryLabel = new QLabel("Geometry Type");
		rowEightLayout->addWidget(geometryLabel);
		geometryTypeChooser = new QComboBox();
		geometryTypeChooser->addItems(geometryTypeList);
		geometryTypeChooser->setCurrentIndex(INITIAL_GEOMTYPE_INDEX);
		rowEightLayout->addWidget(geometryTypeChooser);
	
	rowNineLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowNineLayout);
		detailLabel = new QLabel("Level of Detail");
		rowNineLayout->addWidget(detailLabel);
		detailSlider = new QSlider(Qt::Horizontal);
		rowNineLayout->addWidget(detailSlider);

	resetInterface();
}

GLWindow::~GLWindow()
{
	// Done in reverse-order, bottom of visual hierarchy to the top
	delete detailLabel;
	delete detailSlider;
	delete geometryLabel;
	delete geometryTypeChooser;
	delete colourLabel;
	delete colourChooser;
	delete objectChooserLabel;
	delete objectChooser;
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
	delete rowSixLayout;
	delete rowSevenLayout;
	delete rowEightLayout;
	delete rowNineLayout;
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
	detailSlider->setMinimum(8);
	detailSlider->setMaximum(128);

	update(); // force refresh
	canvasWidget->update(); // wasn't repainting with update()...
}


