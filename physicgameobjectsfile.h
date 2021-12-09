#ifndef PHYSICGAMEOBJECTSFILE_H
#define PHYSICGAMEOBJECTSFILE_H

#include "physicsgameobject.h"

/**
 * @brief All the needed PhysicsGameObjects for the model
 */
class Bowl : public PhysicsGameObject
{
public:
	Bowl();
	int getWaterLevel();
	void setWaterLevel(int newWaterLevel);
	virtual void setBody(b2Body* newBody);
private:
	int waterLevel;
};

class Clock : public PhysicsGameObject
{
public:
	Clock();
	int getTime();
	void setTime(int newTime);

private:
	int time;
};

class Food : public PhysicsGameObject
{
public:
	Food(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef, QImage);
	int getFoodGiven();
	void setFoodGiven(int newFoodGiven);

private:
	int foodGiven;
};

class FoodContainer : public PhysicsGameObject
{
public:
	FoodContainer();
	int getShaken();
	void setShaken(int newShaken);

private:
	int shaken;
};

class Spigot : public PhysicsGameObject
{
public:
	Spigot(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image);
	bool getPower();
	void setPower(bool newPower);

private:
	bool power;
};

class WaterPump : public PhysicsGameObject
{
public:
	WaterPump();
	bool getPower();
	void setPower(bool newPower);

private:
	bool power;
};

class Filter : public PhysicsGameObject
{
public:
	Filter();
	bool getOldFilter();
	void setOldFilter(bool newFilter);

private:
	bool oldFilter;
};

class Siphon : public PhysicsGameObject
{
public:
	Siphon();
};

class Fish : public PhysicsGameObject
{
public:
	Fish(std::string name = "Jim Carey",
		 QPointF position = QPointF(0,-2),
		 double rotation = 0,
		 QPointF scale = QPointF(2,2),
		 QImage image = QImage(":/res/simple_fish.png"));
	bool getInTank();
	void setInTank(bool newInTank);

private:
	bool inTank;
};

class Tank : public PhysicsGameObject{
public:
	Tank(std::string name = "tank",
		 QPointF position = QPointF(0,10),
		 double rotation = 0,
		 QPointF scale = QPointF(10,5));
	bool getWaterLevel();
	void seWaterLevel(bool newWaterLevel);
	virtual void setBody(b2Body* newBody);
private:
	bool waterLevel;
};


class Countertop : public PhysicsGameObject{
public:
	Countertop(double rotation);
	virtual void setBody(b2Body* newBody);
};

#endif // PHYSICGAMEOBJECTSFILE_H
