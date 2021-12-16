#ifndef PHYSICSGAMEOBJECT_H
#define PHYSICSGAMEOBJECT_H

#include <Box2D/Box2D.h>
#include <gameobject.h>
#include <unordered_set>

class PhysicsGameObject : public GameObject
{
protected:
	bool isDynamic;
	b2Body* body;
	b2BodyDef bodyDef;
	bool clickable = false;
public:
	PhysicsGameObject(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef, QImage, int layer =1);
	b2BodyDef getBodyDef();
	b2Body* getBody();
	bool isClickable() const;
	void setClickable(bool);
	void setRotation(double rotation) override;
	static b2BodyDef createBodyDef(b2BodyType);
	virtual void setBody(b2Body* newBody);
	void updateObject(float) override;
	virtual void onCollision(b2Contact* collision, bool isA, PhysicsGameObject* other);
	virtual void onSensor(b2Contact* collision, bool isA, PhysicsGameObject* other);
	virtual void onMouseClick(QPointF mousePosition);
	virtual void onMouseHold(QPointF mousePosition);
	virtual void onMouseRelease(QPointF mousePosition);
private:
	std::unordered_set<std::string> contacts;
	std::unordered_set<std::string> sensorContacts;
	std::unordered_set<std::string> lastContacts;
	std::unordered_set<std::string> lastSensorContacts;
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

#endif // PHYSICSGAMEOBJECT_H
