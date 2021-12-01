#include "fishmodel.h"
#include <QPoint>

FishModel::FishModel()
{

	QString monkeFile = ":/stinkyMonkey.png";
	QImage testMonke(monkeFile);
}

void FishModel::updateGameObjects(){
	tester.updateObject(0.1);
	emit renderGameObjects(tester.getLocation(), tester.getRotation(),tester.getGraphic());
}
