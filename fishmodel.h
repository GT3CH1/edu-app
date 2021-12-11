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
#include "functional"
#include "questsfile.h"

class FishModel : public QObject {

    Q_OBJECT

public:
	enum SCENE_STATE {
		WATER_CHANGE, FILTER_CHANGE, FEEDING, ADD_FISH, PREPARE_TANK
	};
private:
	std::vector<GameObject*> gameObjects;
	std::map<std::string, GameObject*> gameObjectMap;
	float deltaTime;
	b2World physicsWorld;
	PhysicsGameObject* holdObject = nullptr;

	void addGameObjectToScene(GameObject *toAdd);
	GameObject *getGameObject(std::string objectName);
	void deleteGameObject(std::string objectName);
	void addBodyToWorld(PhysicsGameObject *toAdd);
	b2Joint* addJoint(b2JointDef* jointDefinition);
	void destroyJoint(b2Joint* toDestory);

	std::function<void*(std::string)> getGameObjectLambda;
	std::function<void(void*)> addGameObjectLambda;
	std::function<void(std::string)> deleteGameObjectLambda;
	std::function<b2Joint*(b2JointDef*)> addJointLambda;
	std::function<void(b2Joint* toDestory)> destroyJointLambda;

	std::list<Quest*> quests;
	void createQuests();

	bool debug = true;

	QImage getColliderShape(b2Shape *shape, QColor penColor, QPointF &translation);
	// The current scene to draw
	SCENE_STATE currentScene = PREPARE_TANK;
	void setScene(SCENE_STATE currentScene);
	QImage getColliderShape(b2Shape* shape, QColor penColor, QPointF& translation, QPointF& scale);
	CallbackOptions constructCallbackOptions();

	class MouseToPhysicsChecker : public b2QueryCallback
	{
	private:
		PhysicsGameObject* greatestLayer = nullptr;
	public:
		virtual bool ReportFixture(b2Fixture* hit);
		PhysicsGameObject* reportFrontmostObject();
	};

	bool mouseClickProcess(QPointF, PhysicsGameObject*);
	void removeAllGameObjects();

public:
	FishModel(float deltaTime);
	~FishModel();

public slots:
	void updateGameObjects();
	void mouseClick(QPointF);
	void mouseHold(QPointF);
	void mouseRelease(QPointF);
	void nextTask();

signals:
	void renderGameObjects(std::vector<ObjectRenderInformation> renderables);
};

#endif // FISHMODEL_H
