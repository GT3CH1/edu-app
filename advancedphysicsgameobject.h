#ifndef ADVANCEDPHYSICSGAMEOBJECT_H
#define ADVANCEDPHYSICSGAMEOBJECT_H

#include <unordered_set>
#include "physicsgameobject.h"


class AdvancedPhysicsGameObject : public PhysicsGameObject
{
public:
	AdvancedPhysicsGameObject(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef b2BodyDef, QImage image);
private:
	std::unordered_set<std::string> contacts;
	std::unordered_set<std::string> sensorContacts;
	std::unordered_set<std::string> lastContacts;
	std::unordered_set<std::string> lastSensorContacts;
public:
	virtual void onCollision(b2Contact* collision, bool isA, PhysicsGameObject* other);
	virtual void onSensor(b2Contact* collision, bool isA, PhysicsGameObject* other);
	virtual void updateObject(float);
protected:
	//Override these to implement individual logic.
	virtual void onCollisionEnter(b2Contact* collision, bool isA, PhysicsGameObject* other);
	virtual void onCollisionStay(b2Contact* collision, bool isA, PhysicsGameObject* other);
	virtual void onCollisionExit(PhysicsGameObject* other);
	//Override these to implement individual logic.
	virtual void onSensorEnter(b2Contact* collision, bool isA, PhysicsGameObject* other);
	virtual void onSensorStay(b2Contact* collision, bool isA, PhysicsGameObject* other);
	virtual void onSensorExit(PhysicsGameObject* other);
};

#endif // ADVANCEDPHYSICSGAMEOBJECT_H
