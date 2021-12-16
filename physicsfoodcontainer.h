#ifndef FOODCONTAINER_H
#define FOODCONTAINER_H

#include "draggable.h"

class FoodContainer : public Draggable
{
public:
	FoodContainer();
	void setBody(b2Body* newBody) override;
	void updateObject(float deltaTime) override;
private:
	bool shakeUp = true;
	float lastVelocity = 0;
	const float accelerationConstraint = 50;
};


#endif //FOODCONTAINER_H
