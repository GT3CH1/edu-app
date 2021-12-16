/**
 * Authors - William Erignac
 *
 * The large colliders that keep GameObjects
 * in bounds.
 */

#include "physicswall.h"

#include <utility>

/**
 * @brief Constructs a wall game object
 */
Wall::Wall(std::string name, QPointF position, QPointF scale)
	: PhysicsGameObject(std::move(name), position, 0, scale, createBodyDef(b2_staticBody), QImage(":/res/transparent.png"))
{
	render = false;
}

/**
 * @brief Sets the body of the wall game object
 * @param newBody - the body to be set to
 */
void Wall::setBody(b2Body* newBody)
{
	b2PolygonShape rectangle;
	rectangle.SetAsBox(scale.x/2, scale.y/2);
	b2FixtureDef mainFixture;
	mainFixture.shape = &rectangle;
	mainFixture.isSensor = false;
	newBody->CreateFixture(&mainFixture);
	PhysicsGameObject::setBody(newBody);
}
