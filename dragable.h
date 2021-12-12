#ifndef DRAGABLE_H
#define DRAGABLE_H

#include "physicsgameobject.h"

class Dragable : public PhysicsGameObject
{
public:
	class MousePointerObject : public PhysicsGameObject
	{
	public:
		MousePointerObject(QPointF position);
		void setPosition(QPointF position);
		virtual void updateObject(float deltaTime);
	private:
		static b2BodyDef constructBodyDefinition();
	};
private:
	b2MouseJoint* spring = nullptr;
	MousePointerObject* mousePointer;
public:
	Dragable(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef, QImage, int layer);
	virtual void onMouseClick(QPointF position);
	virtual void onMouseHold(QPointF position);
	virtual void onMouseRelease(QPointF position);

};

#endif // DRAGABLE_H
