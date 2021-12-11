#ifndef PHYSICSGAMEOBJECT_H
#define PHYSICSGAMEOBJECT_H

#include <Box2D/Box2D.h>
#include <gameobject.h>

class PhysicsGameObject : public GameObject {
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
	virtual void onMouseClick(QPointF mousePosition);
	virtual void onMouseHold(QPointF mousePosition);
	virtual void onMouseRelease(QPointF mousePosition);
};

#endif // PHYSICSGAMEOBJECT_H
