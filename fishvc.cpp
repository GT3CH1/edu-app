#include "fishvc.h"
#include "./ui_fishvc.h"
#include <QPoint>
#include <QImage>
#include <QTransform>
#include <QTimer>
#include <iostream>

FishVC::FishVC(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::FishVC)
{
	ui->setupUi(this);

	connect(&tutorialModel, &FishModel::renderGameObjects, this, &FishVC::renderGameObjects);

	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, &tutorialModel, &FishModel::updateGameObjects);
	timer->start(80);
}

FishVC::~FishVC()
{
	delete ui;
}

void FishVC::renderGameObjects(QPoint position, double rotation, QImage graphic)
{
	QPixmap composite(512,512);
	QPainter objectRenderer(&composite);
	for (int i = 0; i < 1; i++)
	{
		QTransform RT;
		RT.rotate(rotation); // in degrees
		QPixmap rotatedImage = QPixmap::fromImage(graphic);
		rotatedImage = rotatedImage.transformed(RT);

		QPoint invertedPosition(position.x(), -position.y());
		QPoint center(composite.width()/2, composite.height()/2);
		QPoint spriteCenter(-rotatedImage.width()/2, -rotatedImage.height()/2);
		QPoint upperLeft = invertedPosition + center + spriteCenter;

		objectRenderer.drawImage(upperLeft, rotatedImage.toImage(), QRect(0,0,rotatedImage.width(), rotatedImage.height()));
	}

	ui->label_2->setPixmap(composite);
}

