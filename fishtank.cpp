/**
 * Authors - William Erignac
 * Last Modified - 12/8/2021
 *
 * The FishTank is a static, rectangular GameObject with 3 sides
 * and a sensor in the middle.
 */

#include "fishtank.h"

/**
 * @brief Constructs a FishTank.
 * NOTE: The FishTank doesn't have a physics body upon
 * construction, only a definition.
 */
FishTank::FishTank(std::string name, QPointF position, double rotation, QPointF scale) :
	PhysicsGameObject(name, position, rotation, scale, constructBodyDefinition(), QImage(":/res/simpleTank.png"),0)
{ }

/**
 * @brief Assigns this FishTank a body and adds the 3 walls
 * and sensor to the body.
 */
void FishTank::setBody(b2Body* newBody)
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
	bottomShape.SetAsBox(5,1,b2Vec2(0,-2.5),0);

	b2FixtureDef bottomFixture;
	bottomFixture.shape = &bottomShape;
	bottomFixture.isSensor = false;
	bottomFixture.density = 1;
	bottomFixture.friction = 1;

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

		newBody->CreateFixture(&wallFixture);
	}

	//THIS MUST ALWAYS BE CALLED AT THE END OF A SETBODY FOR ANY PHYSICSGAMEOBJECT.
	PhysicsGameObject::setBody(newBody);
}

/**
 * @brief Detects whether any objects have entered the tank and prints
 * the names of the objects.
 */
void FishTank::onSensor(b2Contact* collision, bool isA, PhysicsGameObject* other)
{
//    std::cout << "I sensed object " << other->getName() << std::endl;
}

/**
 * @brief Returns a body definition for the FishTank.
 */
b2BodyDef FishTank::constructBodyDefinition()
{
	b2BodyDef definition;
	definition.type = b2_staticBody;
	return definition;
}
