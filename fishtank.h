#ifndef FISHTANK_H
#define FISHTANK_H

#include "physicsgameobject.h"

class FishTank : public PhysicsGameObject
{
public:
	FishTank(std::string name, QPointF position, double rotation, QPointF scale);
	virtual void setBody(b2Body* newBody);
private:
	static b2BodyDef constructBodyDefinition();
};

#endif // FISHTANK_H
