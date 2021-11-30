#include "fishmodel.h"
#include <QPoint>

FishModel::FishModel()
{
	QString monkeFile = "latest.png";
	QImage testMonke(monkeFile);
	GameObject temp(QPoint(0, 0), 0, testMonke);
	tester = temp;
}

void FishModel::updateGameObjects(){
	tester.updateObject(0.1);
}
