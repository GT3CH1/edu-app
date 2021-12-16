/**
 * Authors - Alex Richins, Gavin Pease, Kenzie Evans, William Erignac
 *
 * Fills the bowl with water.
 */

#include "physicsspigot.h"
#include "physicsbowl.h"

/**
 * @brief Creates a spigot game object
 */
Spigot::Spigot(QPointF position) :
	PhysicsGameObject("spigot", position, 0, QPointF(1.5, 2.25), PhysicsGameObject::createBodyDef(b2_staticBody), QImage(":/res/spigot.png"))
{
	setClickable(true);
}

/**
 * @brief Sets the body of this game object
 * @param newBody - the body to be set to
 */
void Spigot::setBody(b2Body* newBody)
{
	// Make the sensor...
	b2PolygonShape sensorShape;
	sensorShape.SetAsBox(scale.x / 2, scale.y / 2);
	b2FixtureDef hitBoxDefinition;
	hitBoxDefinition.shape = &sensorShape;
	hitBoxDefinition.isSensor = true;
	newBody->CreateFixture(&hitBoxDefinition);
	PhysicsGameObject::setBody(newBody);
}

/**
 * @brief As the spigot is being held, it should fill
 * the bowl.
 */
void Spigot::onMouseHold(QPointF position)
{
	Bowl* bowl = (Bowl*)callbackOptions.getGameObject("bowl");
	bowl->raiseWaterLevel();
}
