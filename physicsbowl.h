#include "physicsgameobject.h"
class Bowl : public PhysicsGameObject
{
public:
	Bowl();
	int getWaterLevel();
	void setWaterLevel(int newWaterLevel);
	void raiseWaterLevel();
	virtual void setBody(b2Body* newBody);
	void onMouseClick(QPointF position);
private:
	int waterLevel;
	void drawWater();
	QImage emptyBucket;
};