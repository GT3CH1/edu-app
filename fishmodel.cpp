#include "fishmodel.h"
#include <QPoint>

FishModel::FishModel()
{
	QString monkeFile = ":/stinkyMonkey.png";
	QImage testMonke(monkeFile);
	GameObject temp(QPoint(0, 0), 0, testMonke);
	tester = temp;
}

void FishModel::updateGameObjects(){
	tester.updateObject(0.1);
	emit renderGameObjects(tester.getLocation(), tester.getRotation(),tester.getGraphic());
}
