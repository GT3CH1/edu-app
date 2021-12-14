#ifndef FOODCONTAINER_H
#define FOODCONTAINER_H

#include "dragable.h"

class FoodContainer : public Dragable
{
public:
	FoodContainer();
	void setBody(b2Body* newBody) override;
	void updateObject(float deltaTime) override;
private:
	bool shakeUp = true;
	const float angleConstraint = M_PI/4;
	float lastVelocity = 0;
	const float accelerationConstraint = 50;
};


#endif //FOODCONTAINER_H
