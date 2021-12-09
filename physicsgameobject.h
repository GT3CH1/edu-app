#ifndef PHYSICSGAMEOBJECT_H
#define PHYSICSGAMEOBJECT_H

#include <gameobject.h>

class PhysicsGameObject : public GameObject
{
protected:
	bool isDynamic;
	b2Body* body;
	b2BodyDef bodyDef;
	bool clickable = true;
public:
	PhysicsGameObject(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef, QImage, int layer =1);
	b2BodyDef getBodyDef();
	b2Body* getBody();
	bool getIsClickable();
	static b2BodyDef createBodyDef(b2BodyType);
	virtual void setBody(b2Body* newBody);
	virtual void updateObject(float);
	virtual void onCollision(b2Contact* collision, bool isA, PhysicsGameObject* other);
	virtual void onSensor(b2Contact* collision, bool isA, PhysicsGameObject* other);
	virtual void onMouseClick(QPointF position);
	virtual void onMouseHold(QPointF position);
	virtual void onMouseRelease(QPointF position);
};

#endif // PHYSICSGAMEOBJECT_H
