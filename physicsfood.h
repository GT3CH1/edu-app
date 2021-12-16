#ifndef PHYSICSFOOD_H
#define PHYSICSFOOD_H

#include "physicsgameobject.h"
class Food : public PhysicsGameObject
{
public:
	Food(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef);
	void setBody(b2Body* newBody) override;
private:
	static int foodGenerated;
	QImage generateFood();
};

#endif // PHYSICSFOOD_H
