/**
 * Authors - William Erignac
 * Last Modified - 12/9/2021
 *
 * A water droplet (a circular rigidbody).
 */

#include "simpledropplet.h"

/**
 * @brief Constructs a droplet.
 * @param id The ID of the dropplet is appened to its name.
 * All IDs for dropplets should be unique.
 */
SimpleDropplet::SimpleDropplet(int id, QPointF position, double rotation, QPointF scale) :
	PhysicsGameObject("SimpleDropplet " + std::to_string(id), position, rotation, scale, constructBodyDefinition(), QImage(":/res/simpleDropplet.png"),1)
{ clickable = false; }

/**
 * @brief Returns a dynamic body type.
 */
b2BodyDef SimpleDropplet::constructBodyDefinition()
{
	b2BodyDef definition;
	definition.type = b2_dynamicBody;
	return definition;
}

/**
 * @brief Adds the cirular hitbox of the
 * droplet to the provided body.
 */
void SimpleDropplet::setBody(b2Body *newBody)
{
	b2CircleShape hitBoxShape;
	hitBoxShape.m_radius = 0.5;

	b2FixtureDef hitBoxDefinition;

	hitBoxDefinition.shape = &hitBoxShape;
	hitBoxDefinition.density = 1;
	hitBoxDefinition.isSensor = false;
	hitBoxDefinition.friction = 0.5;
	hitBoxDefinition.restitution = 0.9;

	newBody->CreateFixture(&hitBoxDefinition);

	PhysicsGameObject::setBody(newBody);
}
