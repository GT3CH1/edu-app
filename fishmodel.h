#ifndef FISHMODEL_H
#define FISHMODEL_H

#include <QObject>
#include <vector>
#include <map>
#include <queue>
#include "gameobject.h"
#include "objectrenderinformation.h"
#include <Box2D/Box2D.h>
#include "physicsgameobject.h"
#include <functional>
#include "questsfile.h"
#include "scenestate.h"
class FishModel : public QObject
{

	Q_OBJECT
private:
	std::vector<GameObject*> gameObjects;
	std::map<std::string, GameObject*> gameObjectMap;
	float deltaTime;
	float getDeltaTime();
	b2World physicsWorld;
	PhysicsGameObject* holdObject = nullptr;

	void addGameObjectToScene(GameObject *toAdd, bool runStart);
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
	std::function<float()> getDeltaTimeLambda;

	std::queue<Quest*> quests;
	AnimatedFish fishInTank;

	//Debug determines whether to draw object colliders.
	bool debug = false;

	// The current scene to draw
	SCENE_STATE currentScene = START;
	void setScene(SCENE_STATE currentScene);
	QImage getColliderShape(b2Shape* shape, QColor penColor, QPointF& translation, QPointF& scale);
	CallbackOptions constructCallbackOptions();

	class MouseToPhysicsChecker : public b2QueryCallback
	{
	private:
		PhysicsGameObject* greatestLayer = nullptr;
	public:
		bool ReportFixture(b2Fixture* hit) override;
		PhysicsGameObject* reportFrontmostObject();
	};

	bool mouseClickProcess(QPointF, PhysicsGameObject*);
	void removeAllGameObjects();

public:
	explicit FishModel(float deltaTime);
	~FishModel() override;

	struct CollisionEntry
	{
	public:
		CollisionEntry(PhysicsGameObject* first, PhysicsGameObject* second);
		CollisionEntry(PhysicsGameObject* first, PhysicsGameObject* second, bool forcePosition);
		size_t hashCode() const;
		bool operator==(const CollisionEntry& other) const;
	private:
		const PhysicsGameObject* a;
		const PhysicsGameObject* b;
	};

public slots:
	void updateGameObjects();
	void mouseClick(QPointF);
	void mouseHold(QPointF);
	void mouseRelease(QPointF);
	void nextTask();
	void nextQuest();
	void addFishToTank(AnimatedFish *f);

signals:
	void renderGameObjects(std::vector<ObjectRenderInformation> renderables);
};

namespace std
{
	template<>
	/**
	 * @brief Needed for unordered_set of CollisionEntries.
	 */
	struct hash<FishModel::CollisionEntry>
	{
	public:
		size_t operator()(const FishModel::CollisionEntry& toHash) const
		{
			return toHash.hashCode();
		}
	};
}
#endif // FISHMODEL_H
