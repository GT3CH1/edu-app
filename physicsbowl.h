#ifndef PHYSICSBOWL_H
#define PHYSICSBOWL_H

#include "physicsgameobject.h"

class Bowl : public PhysicsGameObject
{
public:
	Bowl(QPointF position);
	int getWaterLevel() const;
	void setWaterLevel(int newWaterLevel);
	void raiseWaterLevel();
	virtual void setBody(b2Body* newBody);
	void onMouseClick(QPointF position);
private:
	int waterLevel;
	void drawWater();
	QImage emptyBucket;
};

#endif // PHYSICSBOWL_H
