#include "fishvc.h"
#include "./ui_fishvc.h"
#include <QPoint>
#include <QImage>
#include <QTransform>
#include <QTimer>

FishVC::FishVC(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::FishVC)
	, tutorialModel(0.1666f)
{
	ui->setupUi(this);

	connect(&tutorialModel, &FishModel::renderGameObjects, this, &FishVC::renderGameObjects);

	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, &tutorialModel, &FishModel::updateGameObjects);
	timer->start(17);
}

FishVC::~FishVC()
{
	delete ui;
}

void FishVC::renderGameObjects(std::vector<ObjectRenderInformation> renderables)
{
	QPixmap composite(512,512);
	QPainter objectRenderer(&composite);

	for (ObjectRenderInformation& renderable : renderables)
	{
		QTransform RT;
		RT.rotate(renderable.rotation); // in degrees
		QPixmap rotatedImage = QPixmap::fromImage(renderable.toRender);
		rotatedImage = rotatedImage.transformed(RT);

		QPoint invertedPosition(renderable.position.x(), -renderable.position.y());
		QPoint center(composite.width()/2, composite.height()/2);
		QPoint spriteCenter(-rotatedImage.width()/2, -rotatedImage.height()/2);
		QPoint upperLeft = invertedPosition + center + spriteCenter;

		objectRenderer.drawImage(upperLeft, rotatedImage.toImage(), QRect(0,0,rotatedImage.width(), rotatedImage.height()));
	}

	ui->label_2->setPixmap(composite);
}

