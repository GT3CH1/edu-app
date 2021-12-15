/**
 * Authors - William Erignac
 * Last Modified - 12/14/2021
 *
 * The large colliders that keep GameObjects
 * in bounds.
 */

#include "physicswall.h"

Wall::Wall(std::string name, QPointF position, QPointF scale)
	: PhysicsGameObject(name, position, 0, scale, createBodyDef(b2_staticBody), QImage(":/res/transparent.png"))
{
	render = false;
}

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
