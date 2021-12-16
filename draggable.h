#ifndef DRAGABLE_H
#define DRAGABLE_H

#include "physicsgameobject.h"

class Draggable : public PhysicsGameObject
{
public:
	class MousePointerObject : public PhysicsGameObject
	{
	public:
		explicit MousePointerObject(QPointF position);

		void updateObject(float deltaTime) override;
	private:
		static b2BodyDef constructBodyDefinition();
	};
protected:
	b2MouseJoint* spring = nullptr;
	MousePointerObject* mousePointer = nullptr;
public:
	Draggable(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef, QImage, int layer);
	void onMouseClick(QPointF position) override;
	void onMouseHold(QPointF position) override;
	void onMouseRelease(QPointF position) override;

};

#endif // DRAGABLE_H
