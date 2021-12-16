#ifndef PHYSICSCLOCK_H
#define PHYSICSCLOCK_H

#include "physicsgameobject.h"

class Clock : public PhysicsGameObject
{
public:
	Clock();
	void start();
	int getTime() const;
	void setTime(int newTime);
	void addTime();
	virtual void setBody(b2Body* newBody);
	void onMouseHold(QPointF position);
private:
	double time;
	double clockRate = 1;
	void drawClock();
	GameObject* hourHand;
	GameObject* minuteHand;
	GameObject* sky;
};

#endif // PHYSICSCLOCK_H
