/**
 * Authors - Alex Richins, William Erignac
 * Last Modified - 12/2/2021
 *
 * The view / controller of the fish training application.
 */

#include "fishvc.h"
#include <QPoint>
#include <QImage>
#include <QTransform>
#include <QTimer>

/**
 * @brief Constructs a view/controller with a model.
 */
FishVC::FishVC(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::FishVC)
	, tutorialModel(0.1666f)
{
	ui->setupUi(this);

	connect(&tutorialModel, &FishModel::renderGameObjects, this, &FishVC::renderGameObjects);

	//Update the model every 0.1666 seconds (60 fps).
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, &tutorialModel, &FishModel::updateGameObjects);
	timer->start(17);
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
	//TODO: Change this to match the dimensions of the RenderArea.
	QPixmap composite(512,512);
	QPainter objectRenderer(&composite);

	//Paint the renderables one by one onto the composite.
	for (ObjectRenderInformation& renderable : renderables)
	{
		//Rotation and scaling transformations.
		QPixmap rotatedImage = QPixmap::fromImage(renderable.toRender);
		QTransform scale;
		scale.scale(renderable.scale.x(), renderable.scale.y());
		QTransform rotation;
		rotation.rotate(-renderable.rotation);
		rotatedImage = rotatedImage.transformed(scale).transformed(rotation);

		//Perform model-to-view space transformations.
		//TODO: Include a scale operation in the transformations
		//so that the model and view aren't 1 to 1 (1 pixel = 1 meter
		//is a super zoomed out scale).
		QPoint invertedPosition(renderable.position.x(), -renderable.position.y());
		QPoint center(composite.width()/2, composite.height()/2);
		QPoint spriteCenter(-rotatedImage.width()/2, -rotatedImage.height()/2);
		QPoint upperLeft = invertedPosition + center + spriteCenter;

		//Draw the renderable.
		objectRenderer.drawImage(upperLeft, rotatedImage.toImage(), QRect(0,0,rotatedImage.width(), rotatedImage.height()));
	}

	ui->label_2->setPixmap(composite);
}

