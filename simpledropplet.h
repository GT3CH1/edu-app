#ifndef SIMPLEDROPPLET_H
#define SIMPLEDROPPLET_H

#include "physicsgameobject.h"

class SimpleDropplet : public PhysicsGameObject
{
public:
	SimpleDropplet(int id, QPointF position, double rotation, QPointF scale);
	virtual void setBody(b2Body* newBody);
private:
	static b2BodyDef constructBodyDefinition();
};

#endif // SIMPLEDROPPLET_H
