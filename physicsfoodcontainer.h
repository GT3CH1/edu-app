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
	const float velocityThreshold = 0.1;
	const float accelerationConstraint = 100;
};


#endif //FOODCONTAINER_H
