#include "physicsgameobject.h"
class Countertop : public PhysicsGameObject{
public:
	Countertop(QPointF position, QPointF(scale));
	virtual void setBody(b2Body* newBody);
};
