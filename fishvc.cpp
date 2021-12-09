/**
 * Authors - Alex Richins, William Erignac, Jonathan Vielstich
 * Last Modified - 12/8/2021
 *
 * The view / controller of the fish training application.
 */

#include "fishvc.h"
#include <QPoint>
#include <QTransform>
#include <QTimer>
#include <QPushButton>
#include <iostream>

/**
 * @brief Constructs a view/controller with a model.
 */
FishVC::FishVC(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::FishVC)
	, tutorialModel(0.1666f)
{
	ui->setupUi(this);

	ui->centralwidget->setMinimumSize(WINDOW_MIN);
	ui->mainCanvas->setMinimumSize(CANVAS_MIN);

	connect(&tutorialModel, &FishModel::renderGameObjects, this, &FishVC::renderGameObjects);

	//Update the model every 0.1666 seconds (60 fps).
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, &tutorialModel, &FishModel::updateGameObjects);
	timer->start(FPS);

	mouseTimer = new QTimer(this);
	mouseTimer->setInterval(FPS);
	connect(mouseTimer, &QTimer::timeout, this, &FishVC::mouseHold);

	// Connect mouse controls
	connect(ui->mainCanvas, &RenderArea::mousePressed, this, &FishVC::mouseClick);
	connect(ui->mainCanvas, &RenderArea::mouseLocation, this, &FishVC::mouseMove);
	connect(ui->mainCanvas, &RenderArea::mouseReleased, this, &FishVC::mouseRelease);
	connect(this, &FishVC::mouseClickSignal, &tutorialModel, &FishModel::mouseClick);
	connect(this, &FishVC::mouseHoldSignal, &tutorialModel, &FishModel::mouseHold);
	connect(this, &FishVC::mouseReleaseSignal, &tutorialModel, &FishModel::mouseRelease);
}

FishVC::~FishVC()
{
	delete ui;
}

/**
 * @brief Renders the images with the provided transformations in renderables.
 */
void FishVC::renderGameObjects(std::vector<ObjectRenderInformation> renderables)
{
	QPixmap composite(ui->mainCanvas->width(),ui->mainCanvas->height());
	QPainter objectRenderer(&composite);
	float ratio = (float)ui->mainCanvas->width() / MODEL_SCALE;

	//Paint the renderables one by one onto the composite.
	for (ObjectRenderInformation& renderable : renderables)
	{
		//Rotation and scaling transformations.
		QPixmap rotatedImage = QPixmap::fromImage(renderable.toRender);
		QTransform scale;
		scale.scale(renderable.scale.x() * ratio / renderable.toRender.width(), renderable.scale.y() * ratio / renderable.toRender.height());
		QTransform rotation;
		rotation.rotate(-renderable.rotation);
		rotatedImage = rotatedImage.transformed(scale).transformed(rotation);

		//Perform model-to-view space transformations.
		QPointF spriteCenter((float)-rotatedImage.width() / 2.0f, (float)-rotatedImage.height() / 2.0f);
		QPointF upperLeft = modelToView(renderable.position) + spriteCenter;

		//Draw the renderable
		objectRenderer.drawImage(upperLeft, rotatedImage.toImage(), QRect(0,0,rotatedImage.width(), rotatedImage.height()));
	}

	ui->mainCanvas->setImage(composite);
	objectRenderer.end();
}

/**
 * Converts a point from the model coordinate system to the view coordinate system.
 * @param point
 * @return the same point in the view
 */
QPointF FishVC::modelToView(QPointF point)
{
	float x = (float)(point.x() * (1.0f / modelRatio)) + (float)ui->mainCanvas->width() / 2.0f;
	float y = (float)(-1.0f * point.y() * (1.0f / modelRatio)) + ((float)ui->mainCanvas->height() / 2.0f);
	return {x, y};
}

/**
 * Converts a point from the view coordinate system to the model coordinate system.
 * @param point
 * @return the same point in the model
 */
QPointF FishVC::viewToModel(QPointF point)
{
	float x = ((float)point.x() - ((float)ui->mainCanvas->width() / 2.0f)) * modelRatio;
	float y = (-1.0f * ((float)point.y() - ((float)ui->mainCanvas->height() / 2.0f))) * modelRatio;
	return {x, y};
}

/**
 * Emits the mouse position once when the left mouse button is pressed.
 * @param position
 */
void FishVC::mouseClick(QPointF position)
{
	mousePosition = viewToModel(position);
	emit mouseClickSignal(mousePosition);
	mouseTimer->start();
}

/**
 * Updates the mouse position when it is moved while the left mouse button is pressed.
 * @param position
 */
void FishVC::mouseMove(QPointF position)
{
	mousePosition = viewToModel(position);
}

/**
 * Emits the mouse position once when the left mouse button is released.
 * @param position
 */
void FishVC::mouseRelease(QPointF position)
{
	mouseTimer->stop();
	mousePosition = viewToModel(position);
	emit mouseReleaseSignal(mousePosition);
}

/**
 * Emits the mouse position once a frame as long as the left mouse button is pressed.
 */
void FishVC::mouseHold()
{
	emit mouseHoldSignal(mousePosition);
}

/**
 * Resizes the main canvas to match the new window size.
 *
 * Overrides the default resizeEvent method.
 * @param event
 */
void FishVC::resizeEvent(QResizeEvent *event)
{
	// Get new window dimensions
	int w = ui->centralwidget->width();
	int h = ui->centralwidget->height();

	// Find new dimensions for mainCanvas
	int canvasW = (int)(w * (CANVAS_MIN.width() / (double)WINDOW_MIN.width()));
	int canvasH = (int)(h * (CANVAS_MIN.height() / (double)WINDOW_MIN.height()));
	int canvasX = (int)((w - canvasW) / 2.0);
	int canvasY = (int)((h - canvasH) / 2.0);

	// Set new mainCanvas size and position
	ui->mainCanvas->resize(canvasW, canvasH);
	ui->mainCanvas->move(canvasX, canvasY);

	// Redefine modelRatio
	modelRatio = MODEL_SCALE / (float)ui->mainCanvas->width();
}
