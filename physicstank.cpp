/**
 * Authors - William Erginac, Kenzie Evans, Alex Richins, Gavin Pease
 *
 * The aquarium used in all levels. Keeps track of or detect:
 * - Water level
 * - Food
 * - Fish
 */

#include "physicstank.h"
#include "physicsfish.h"
#include "physicsfood.h"
#include <QPainter>
#include <QDebug>
#include <utility>
// Tank
Tank::Tank(std::string name, QPointF position, double rotation, QPointF scale) :
	PhysicsGameObject(std::move(name), position, rotation, scale, PhysicsGameObject::createBodyDef(b2_staticBody), QImage(":/res/simpleTank.png"), 3)
{
	waterLevel = 0;
	emptyTank = graphic;
}

/**
 * @brief Sets the body of the tank game object
 * @param newBody - the body to be set to
 */
void Tank::setBody(b2Body* newBody)
{
	// Make the sensor...
	b2PolygonShape sensorShape;
	sensorShape.SetAsBox(4, 2);
	b2FixtureDef hitBoxDefinition;
	hitBoxDefinition.shape = &sensorShape;
	hitBoxDefinition.isSensor = true;
	hitBoxDefinition.density = 1;
	hitBoxDefinition.friction = 1;
	newBody->CreateFixture(&hitBoxDefinition);
	//Make the bottom...
	b2PolygonShape bottomShape;
	bottomShape.SetAsBox(5, 0.25, b2Vec2(0, -2), 0);
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
		wall.SetAsBox(0.5, 2.5, b2Vec2(-4.5, 0), 0);
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
		wall.SetAsBox(0.5, 2.5, b2Vec2(4.5, 0), 0);
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

/**
 * @brief Gets the current water level.
 * @return A percentage of how full the water in the tank is.
 */
int Tank::getWaterLevel() const
{
	return waterLevel;
}

/**
 * @brief Sets the water level of the tank to a given percentage.
 * @param newWaterLevel - The new percentage of water in the tank, capped to values between 0 and 100.
 */
void Tank::setWaterLevel(int newWaterLevel)
{
	if(waterLevel > 100)
		waterLevel = 100;

	if (waterLevel < 0)
		waterLevel = 0;

	waterLevel = newWaterLevel;
	drawWater();
}

/**
 * @brief Draws the current level of water in the tank.
 */
void Tank::drawWater()
{
	//Start with an empty canvas.
	QImage water(emptyTank.width(), emptyTank.height(), QImage::Format::Format_RGBA64);
	water.fill(Qt::transparent);
	QPainter painter(&water);
	//Draw the water as a rectangle behind the tank.
	painter.setBrush(QColor(0, 75, 225, 225));
	painter.drawRect(0, emptyTank.height() - waterLevel*emptyTank.height()/100, emptyTank.width()-2, waterLevel*emptyTank.height()/100);
	//Draw the tank.
	painter.drawImage(QPointF(0, 0), emptyTank);
	painter.end();
	graphic = water;
}

/**
 * @brief Detects when an object enters the tank
 */
void Tank::onSensorEnter(b2Contact *collision, bool isA, PhysicsGameObject *other)
{
	//Apply drag to submerged objects
	other->getBody()->SetLinearDamping(other->getBody()->GetLinearDamping()*5);
	other->getBody()->SetAngularDamping(other->getBody()->GetAngularDamping()*5);
	//Check for important objects that have entered the tank.
	auto fish = dynamic_cast<Fish*>(other);
	auto food = dynamic_cast<Food*>(other);

	if(fish != nullptr)
		fish->setInTank(true);

	else if (food)
		incrementFoodInTank();
}

/**
 * @brief Detects when an object leaves the tank
 */
void Tank::onSensorExit(PhysicsGameObject *other)
{
	//Get rid of the drag caused by being in water.
	other->getBody()->SetLinearDamping(other->getBody()->GetLinearDamping()/5);
	other->getBody()->SetAngularDamping(other->getBody()->GetAngularDamping()/5);
}

/**
 * @brief Gets how much food is in the tank.
 */
int Tank::getFoodInTank() const
{
	return foodInTank;
}

/**
 * @brief Increments the amount of food that has been disperesed into the tank by one.
 */
void Tank::incrementFoodInTank()
{
	foodInTank++;
}
