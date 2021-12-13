#include "physicsgameobject.h"
class Countertop : public PhysicsGameObject{
public:
	Countertop(double rotation);
	virtual void setBody(b2Body* newBody);
};