/**
 * Authors - William Erignac
 * Last Modified - 12/9/2021
 *
 * An example object that can be dragged onscreen.
 */

#include "simpledragable.h"

/**
 * @brief Creates a basic dragable object with the given parameters.
 */
SimpleDragable::SimpleDragable(std::string name, QPointF position, double rotation, QPointF scale, int layer)
	: Dragable(name, position, rotation, scale, constructBodyDef(), QImage(":/res/stinkyMonkey.png"), layer)
{ }

/**
 * @brief Sets the body to be a 2.5 by 2 rectangle.
 */
void SimpleDragable::setBody(b2Body* newBody)
{
	b2PolygonShape square;
	square.SetAsBox(1.25,1);

	b2FixtureDef mainFixtureDef;
	mainFixtureDef.shape = &square;
	mainFixtureDef.density = 10;
	mainFixtureDef.friction = 0.1;
	mainFixtureDef.restitution = 0.2;
	mainFixtureDef.isSensor = false;

	newBody->CreateFixture(&mainFixtureDef);

	PhysicsGameObject::setBody(newBody);
}

/**
 * @brief Constructs a simple dynamic body.
 */
b2BodyDef SimpleDragable::constructBodyDef()
{
	b2BodyDef definition;
	definition.type = b2BodyType::b2_dynamicBody;
	return definition;
}
