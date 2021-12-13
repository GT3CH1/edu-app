#include "physicsgameobject.h"

class Clock : public PhysicsGameObject
{
public:
	Clock();
	int getTime();
	void setTime(int newTime);
	void addTime();
	virtual void setBody(b2Body* newBody);
	void onMouseHold(QPointF position);
private:
	int time;
	void drawClock();
	QImage baseClock;
};