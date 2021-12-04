/**
 * Authors - William Erignac
 * Last Modified - 12/3/2021
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
	PhysicsGameObject(name, position, rotation, scale, constructBodyDefinition(), QImage(QString(":/simpleTank.png")))
{ }

/**
 * @brief Assigns this FishTank a body and adds the 3 walls
 * and sensor to the body.
 */
void FishTank::setBody(b2Body* newBody)
{
	// Make the sensor...
	b2PolygonShape sensorShape;
	sensorShape.SetAsBox(100.0f, 50.0f);

	b2FixtureDef hitBoxDefinition;
	hitBoxDefinition.shape = &sensorShape;
	hitBoxDefinition.isSensor = true;

	newBody->CreateFixture(&hitBoxDefinition);

	//Make the bottom...
	b2PolygonShape bottomShape;
	bottomShape.SetAsBox(110,10,b2Vec2(0,-55),0);

	b2FixtureDef bottomFixture;
	bottomFixture.shape = &bottomShape;
	bottomFixture.isSensor = false;

	newBody->CreateFixture(&bottomFixture);

	//Make the left wall...
	{
		b2PolygonShape wall;
		wall.SetAsBox(10,60,b2Vec2(-100,0),0);

		b2FixtureDef wallFixture;
		wallFixture.shape = &wall;
		wallFixture.isSensor = false;

		newBody->CreateFixture(&wallFixture);
	}

	//Make the right wall...
	{
		b2PolygonShape wall;
		wall.SetAsBox(10,60,b2Vec2(100,0),0);

		b2FixtureDef wallFixture;
		wallFixture.shape = &wall;
		wallFixture.isSensor = false;

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
