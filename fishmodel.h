#ifndef FISHMODEL_H
#define FISHMODEL_H

#include <QObject>
#include "gameobject.h"

class FishModel : public QObject
{

	Q_OBJECT

private:
	GameObject tester;

public:
	FishModel();

public slots:
	void updateGameObjects();

signals:
	void renderGameObjects(QPoint, double, QImage);
};

#endif // FISHMODEL_H
