#ifndef PHYSICGAMEOBJECTSFILE_H
#define PHYSICGAMEOBJECTSFILE_H

#include "physicsgameobject.h"

/**
 * @brief All the needed PhysicsGameObjects for the model
 */

class Bowl : public PhysicsGameObject
{
public:
	Bowl(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image);
	int getWaterLevel();
	void setWaterLevel(int newWaterLevel);
private:
	int waterLevel;
};

class Clock : public PhysicsGameObject
{
public:
	Clock(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image);
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
	FoodContainer(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image);
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
	WaterPump(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image);
	bool getPower();
	void setPower(bool newPower);

private:
	bool power;
};

class Filter : public PhysicsGameObject
{
public:
	Filter(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image);
	bool getOldFilter();
	void setOldFilter(bool newFilter);

private:
	bool oldFilter;
};

class Siphon : public PhysicsGameObject
{
public:
	Siphon(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image);
};

class Fish : public PhysicsGameObject
{
public:
	Fish(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image);
	bool getInTank();
	void setInTank(bool newInTank);

private:
	bool inTank;
};

class Tank : public PhysicsGameObject{
public:
	Tank(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image);
	bool getWaterLevel();
	void seWaterLevel(bool newWaterLevel);

private:
	bool waterLevel;
};

#endif // PHYSICGAMEOBJECTSFILE_H
