/**
 * Authors - William Erginac, Kenzie Evans, Gavin Pease
 * Last Modified - 12/12/2021
 *
 * The base floor of all levels.
 */
#include "physicscountertop.h"
Countertop::Countertop(QPointF _position, QPointF _scale)
		: PhysicsGameObject("countertop",_position,0,_scale,createBodyDef(b2_staticBody),QImage(":/res/counter.png")){

}

void Countertop::setBody(b2Body *newBody) {
	b2PolygonShape wall;
	wall.SetAsBox(scale.x/2,scale.y/2);

	b2FixtureDef wallFixture;
	wallFixture.shape = &wall;
	wallFixture.isSensor = false;
	wallFixture.friction = 1;
	wallFixture.restitution = 0.1;

	newBody->CreateFixture(&wallFixture);
	PhysicsGameObject::setBody(newBody);
}
