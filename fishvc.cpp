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
//	QTransform RT;
//	RT.rotate(rotation); // in degrees
//	RT.translate(position.x(), position.y());
	QPixmap rotatedImage;
	rotatedImage.convertFromImage(graphic);
//	rotatedImage.transformed(RT);

	if (rotatedImage.isNull()){
		std::cout << "stinky image no load";
	}
	ui->label->setPixmap(rotatedImage);
}

