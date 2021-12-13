/**
 * Authors - Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */

#include "physicsspigot.h"
#include "physicsbowl.h"
// Spigot
Spigot::Spigot() : PhysicsGameObject("spigot", QPointF(-8, 0), 0, QPointF(1,1), PhysicsGameObject::createBodyDef(b2_staticBody), QImage(":/res/spigot.png"))
{
	power = false;
	setClickable(true);
}

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

void Spigot::setBody(b2Body* newBody)
{
	// Make the sensor...
	b2PolygonShape sensorShape;
	sensorShape.SetAsBox(0.5, 0.5);

	b2FixtureDef hitBoxDefinition;
	hitBoxDefinition.shape = &sensorShape;
	hitBoxDefinition.isSensor = true;

	newBody->CreateFixture(&hitBoxDefinition);
	PhysicsGameObject::setBody(newBody);
}

void Spigot::onMouseHold(QPointF position)
{
	Bowl* bowl = (Bowl*)callbackOptions.getGameObject("bowl");
	bowl->raiseWaterLevel();
}
