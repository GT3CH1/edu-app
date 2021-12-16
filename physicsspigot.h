#ifndef PHYSICSSPIGOT_H
#define PHYSICSSPIGOT_H

#include "physicsgameobject.h"

class Spigot : public PhysicsGameObject
{
public:
	explicit Spigot(QPointF position);
	void setBody(b2Body* newBody) override;
	void onMouseHold(QPointF position) override;
};

#endif // PHYSICSSPIGOT_H
