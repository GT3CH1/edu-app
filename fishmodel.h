#ifndef FISHMODEL_H
#define FISHMODEL_H

#include <QObject>
#include "gameobject.h"
#include <vector>
#include "objectrenderinformation.h"
#include "monkeygameobject.h"

class FishModel : public QObject {

    Q_OBJECT

private:
	std::vector<GameObject*> gameObjects;
	float deltaTime;

public:
	FishModel(float deltaTime);
	~FishModel();

public slots:
	void updateGameObjects();

signals:
	void renderGameObjects(std::vector<ObjectRenderInformation> renderables);
};

#endif // FISHMODEL_H
