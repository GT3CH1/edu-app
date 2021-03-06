#ifndef PHYSICSTANK_H
#define PHYSICSTANK_H

#include "physicsgameobject.h"

class Tank : public PhysicsGameObject
{
public:
	Tank(std::string name = "tank",
		 QPointF position = QPointF(4.5, -2.25),
		 double rotation = 0,
		 QPointF scale = QPointF(10, 5));
	int getWaterLevel() const;
	void setWaterLevel(int newWaterLevel);
	virtual void setBody(b2Body *newBody);
	void onSensorEnter(b2Contact *collision, bool isA, PhysicsGameObject *other);
	void onSensorExit(PhysicsGameObject *other);
private:
	int waterLevel = 0;
	int foodInTank = 0;
public:
	int getFoodInTank() const;
	void incrementFoodInTank();
private:
	void drawWater();
	QImage emptyTank;
};

#endif // PHYSICSTANK_H
