#ifndef PHYSICSWALL_H
#define PHYSICSWALL_H

#include <physicsgameobject.h>

class Wall : public PhysicsGameObject
{
public:
	Wall(std::string name, QPointF position, QPointF scale);
	void setBody(b2Body* newBody) override;
};

#endif // PHYSICSWALL_H
