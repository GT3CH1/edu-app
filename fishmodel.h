#ifndef FISHMODEL_H
#define FISHMODEL_H

#include <QObject>
#include <vector>
#include <map>
#include "gameobject.h"
#include "objectrenderinformation.h"
#include "monkeygameobject.h"

class FishModel : public QObject {

    Q_OBJECT

private:
	std::vector<GameObject*> gameObjects;
	std::map<std::string, GameObject*> gameObjectMap;
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
