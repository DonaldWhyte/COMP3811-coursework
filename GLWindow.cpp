#include "GLWindow.h"

static const int INITIAL_OBJECT_INDEX = 1;

GLWindow::GLWindow(QWidget* parent, Drawable* drawableObject)
	: QWidget(parent), drawable(drawableObject)
{
	// Define list of drawable objects
	QStringList objectNameList;
	objectNameList << "Tetrahedron" << "Cube" << "Octahedron" << "Dodecahedron" << "Icosahedron";

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

	rotationLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	rowTwoLayout->addLayout(rotationLayout);
		rotationDial = new QDial();
		rotationLayout->addWidget(rotationDial);
		animationCheckBox = new QCheckBox("Animate Polygon");
		rotationLayout->addWidget(animationCheckBox);

	rowThreeLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowThreeLayout);
		renderModeLabel = new QLabel("Render Mode");
		pointRadio = new QRadioButton("Points");
		lineRadio = new QRadioButton("Lines");
		triangleRadio = new QRadioButton("Triangles");
		rowThreeLayout->addWidget(renderModeLabel);
		rowThreeLayout->addWidget(pointRadio);
		rowThreeLayout->addWidget(lineRadio);
		rowThreeLayout->addWidget(triangleRadio);

	rowFourLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowFourLayout);
		objectChooserLabel = new QLabel("Platonic Solid");
		rowFourLayout->addWidget(objectChooserLabel);
		objectChooser = new QComboBox();
		objectChooser->addItems(objectNameList);
		objectChooser->setCurrentIndex(INITIAL_OBJECT_INDEX);
		rowFourLayout->addWidget(objectChooser);
		colourTrianglesCheckBox = new QCheckBox("Colour Triangles");
		rowFourLayout->addWidget(colourTrianglesCheckBox);

	resetInterface();
}

GLWindow::~GLWindow()
{
	// Done in reverse-order, bottom of visual hierarchy to the top
	delete colourTrianglesCheckBox;
	delete objectChooserLabel;
	delete objectChooser;
	delete yLabel;
	delete ySlider;
	delete rotationDial;
	delete animationCheckBox;
	delete xLabel;
	delete rotationLayout;
	delete xSlider;
	delete ySliderLayout;
	delete canvasWidget;
	delete renderModeLabel;
	delete pointRadio;
	delete lineRadio;
	delete triangleRadio;
	delete rowOneLayout;
	delete rowTwoLayout;
	delete rowThreeLayout;
	delete rowFourLayout;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
}

void GLWindow::setDrawable(Drawable* newDrawable)
{
	drawable = newDrawable;
}

void GLWindow::resetInterface()
{
	// TODO: fix bug when going from Triangle rendering mode to lines/points"
	//       you have to click twice on a different mode for the redraw to happen
	xSlider->setMinimum(-100);
	xSlider->setMaximum(100);
	xSlider->setValue( static_cast<int>(drawable->x() * 100.0f) );
	ySlider->setMinimum(-100);
	ySlider->setMaximum(100);
	ySlider->setValue( static_cast<int>(drawable->y() * 100.0f) );

	rotationDial->setMinimum(0);
	rotationDial->setMaximum(360);
	rotationDial->setValue(drawable->rotationDegrees());

	RenderMethod renderMethod = drawable->renderMethod();
	switch (renderMethod)
	{
	case RENDER_METHOD_POINTS:
		pointRadio->setChecked(true);
		break;
	case RENDER_METHOD_LINES:
		lineRadio->setChecked(true);
		break;
	case RENDER_METHOD_TRIANGLES:
		triangleRadio->setChecked(true);
		break;
	}

	update(); // force refresh
	canvasWidget->update(); // wasn't repainting with update()...
}


