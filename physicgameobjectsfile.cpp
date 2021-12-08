#include "physicgameobjectsfile.h"

// Bowl
Bowl::Bowl(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image) :
	PhysicsGameObject(name, position, rotation, scale, body, image)
{
	waterLevel = 0;
}

int Bowl::getWaterLevel()
{
	return waterLevel;
}

void Bowl::setWaterLevel(int newWaterLevel)
{
	waterLevel = newWaterLevel;
}

// Clock
Clock::Clock(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image) :
	PhysicsGameObject(name, position, rotation, scale, body, image)
{
	time = 0;
}

int Clock::getTime()
{
	return time;
}

void Clock::setTime(int newTime)
{
	time = newTime;
}

// Food
Food::Food(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image) :
	PhysicsGameObject(name, position, rotation, scale, body, image)
{
	foodGiven = 0;
}

int Food::getFoodGiven()
{
	return foodGiven;
}

void Food::setFoodGiven(int newFoodGiven)
{
	foodGiven = newFoodGiven;
}

// Food Container
FoodContainer::FoodContainer(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image) :
	PhysicsGameObject(name, position, rotation, scale, body, image)
{
	shaken = 0;
}

int FoodContainer::getShaken()
{
	return shaken;
}

void FoodContainer::setShaken(int newShaken)
{
	shaken = newShaken;
}

// Spigot
Spigot::Spigot(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image) :
	PhysicsGameObject(name, position, rotation, scale, body, image)
{
	power = false;
}

bool Spigot::getPower()
{
	return power;
}

void Spigot::setPower(bool newPower)
{
	power = newPower;
}

// WaterPump
WaterPump::WaterPump(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image) :
	PhysicsGameObject(name, position, rotation, scale, body, image)
{
	power = false;
}

bool WaterPump::getPower()
{
	return power;
}

void WaterPump::setPower(bool newPower)
{
	power = newPower;
}

// Filter
Filter::Filter(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image) :
	PhysicsGameObject(name, position, rotation, scale, body, image)
{
	oldFilter = false;
}

bool Filter::getOldFilter()
{
	return oldFilter;
}

void Filter::setOldFilter(bool newFilter)
{
	oldFilter = newFilter;
}

// Siphon
Siphon::Siphon(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image) :
	PhysicsGameObject(name, position, rotation, scale, body, image) { }

// Fish
Fish::Fish(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image) :
	PhysicsGameObject(name, position, rotation, scale, body, image)
{
	inTank = false;
}

bool Fish::getInTank()
{
	return inTank;
}

void Fish::setInTank(bool newInTank)
{
	inTank = newInTank;
}

// Tank
Tank::Tank(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image):
	PhysicsGameObject(name, position, rotation, scale, body, image)
{
	waterLevel = 0;
}
bool Tank::getWaterLevel()
{
	return waterLevel;
}
void Tank::seWaterLevel(bool newWaterLevel)
{
	waterLevel = newWaterLevel;
}
