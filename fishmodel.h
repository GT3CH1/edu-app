#ifndef FISHMODEL_H
#define FISHMODEL_H

#include <QObject>
#include <vector>
#include <map>
#include "gameobject.h"
#include "objectrenderinformation.h"
#include "monkeygameobject.h"
#include <Box2D/Box2D.h>
#include "physicsgameobject.h"

class FishModel : public QObject {

    Q_OBJECT

private:
	std::vector<GameObject*> gameObjects;
	std::map<std::string, GameObject*> gameObjectMap;
	float deltaTime;
	b2World physicsWorld;

	void addGameObjectToScene(GameObject* toAdd);
	void addBodyToWorld(PhysicsGameObject* toAdd);

	bool debug = true;

	QImage getColliderShape(b2Shape* shape, QColor penColor, QPointF& translation);

public:
	FishModel(float deltaTime);
	~FishModel();

public slots:
	void updateGameObjects();

signals:
	void renderGameObjects(std::vector<ObjectRenderInformation> renderables);
};

#endif // FISHMODEL_H
