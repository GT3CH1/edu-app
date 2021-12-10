#include "physicgameobjectsfile.h"

// Bowl
Bowl::Bowl() :
	PhysicsGameObject("bowl", QPointF(-8,-4), 0, QPointF(3,1.5), PhysicsGameObject::createBodyDef(b2_dynamicBody), QImage(":/res/bowl.png"))
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

void Bowl::setBody(b2Body *newBody) {
	b2PolygonShape wall;
	wall.SetAsBox(1,0.75,b2Vec2(0,0),0);

	b2FixtureDef wallFixture;
	wallFixture.shape = &wall;
	wallFixture.isSensor = false;

	newBody->CreateFixture(&wallFixture);
	PhysicsGameObject::setBody(newBody);
}


// Clock
Clock::Clock() :
	PhysicsGameObject("clock", QPointF(-8,5), 0, QPointF(2,2), PhysicsGameObject::createBodyDef(b2_staticBody), QImage(":/res/clock.png"))
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
FoodContainer::FoodContainer() :
	PhysicsGameObject("foodcontainer", QPointF(-5,-4), 0, QPointF(1,1), createBodyDef(b2_staticBody), QImage(":/res/food_shaker.png"))
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
WaterPump::WaterPump() :
	PhysicsGameObject("waterpump", QPointF(-5.5,-4.25), 0, QPointF(1,1), PhysicsGameObject::createBodyDef(b2_staticBody), QImage(":/res/pump.png"))
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
Filter::Filter() :
	PhysicsGameObject("filter", QPointF(-3.8,-0.1), 0, QPointF(1,1), PhysicsGameObject::createBodyDef(b2_staticBody), QImage(":/res/filter.png"))
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
Siphon::Siphon() :
	PhysicsGameObject("siphon", QPointF(7,-3.75), 0, QPointF(2,2), createBodyDef(b2_staticBody), QImage(":/res/siphon.png")) { }

// Fish
Fish::Fish(std::string name, QPointF position, double rotation, QPointF scale, QImage image) :
	PhysicsGameObject(name, position, rotation, scale, createBodyDef(b2_staticBody), image)
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
Tank::Tank(std::string name, QPointF position, double rotation, QPointF scale) :
	PhysicsGameObject(name, position, rotation, scale, PhysicsGameObject::createBodyDef(b2_dynamicBody), QImage(":/res/simpleTank.png"))
{
	waterLevel = 0;
}

void Tank::setBody(b2Body* newBody)
{
	// Make the sensor...
	b2PolygonShape sensorShape;
	sensorShape.SetAsBox(5, 2.5);

	b2FixtureDef hitBoxDefinition;
	hitBoxDefinition.shape = &sensorShape;
	hitBoxDefinition.isSensor = true;
	hitBoxDefinition.density = 1;
	hitBoxDefinition.friction = 1;

	newBody->CreateFixture(&hitBoxDefinition);

	//Make the bottom...
	b2PolygonShape bottomShape;
	bottomShape.SetAsBox(5,0.25,b2Vec2(0,-2),0);

	b2FixtureDef bottomFixture;
	bottomFixture.shape = &bottomShape;
	bottomFixture.isSensor = false;
	bottomFixture.density = 1;
	bottomFixture.friction = 1;
	bottomFixture.restitution = 0.25;

	newBody->CreateFixture(&bottomFixture);

	//Make the left wall...
	{
		b2PolygonShape wall;
		wall.SetAsBox(0.5,2.5,b2Vec2(-5,0),0);

		b2FixtureDef wallFixture;
		wallFixture.shape = &wall;
		wallFixture.isSensor = false;
		wallFixture.density = 1;
		wallFixture.friction = 1;
		wallFixture.restitution = 0.25;


		newBody->CreateFixture(&wallFixture);
	}

	//Make the right wall...
	{
		b2PolygonShape wall;
		wall.SetAsBox(0.5,2.5,b2Vec2(5,0),0);

		b2FixtureDef wallFixture;
		wallFixture.shape = &wall;
		wallFixture.isSensor = false;
		wallFixture.density = 1;
		wallFixture.friction = 1;
		wallFixture.restitution = 0.25;

		newBody->CreateFixture(&wallFixture);
	}
	newBody->SetAngularDamping(0);

	//THIS MUST ALWAYS BE CALLED AT THE END OF A SETBODY FOR ANY PHYSICSGAMEOBJECT.
	PhysicsGameObject::setBody(newBody);
}

bool Tank::getWaterLevel()
{
	return waterLevel;
}
void Tank::seWaterLevel(bool newWaterLevel)
{
	waterLevel = newWaterLevel;
}

Countertop::Countertop(double rotation)
: PhysicsGameObject("countertop",QPointF(0,-5),rotation,QPointF(20,0.5),createBodyDef(b2_staticBody),QImage(":/res/counter.png")){

}

void Countertop::setBody(b2Body *newBody) {
		b2PolygonShape wall;
		wall.SetAsBox(20,0.25,b2Vec2(0,0),0);

		b2FixtureDef wallFixture;
		wallFixture.shape = &wall;
		wallFixture.isSensor = false;
		wallFixture.friction = 1;
		wallFixture.restitution = 0.1;

		newBody->CreateFixture(&wallFixture);
		PhysicsGameObject::setBody(newBody);
}
