/**
 * Authors - William Erginac, Kenzie Evans, Gavin Pease
 * Last Modified - 12/12/2021
 */
#include "physicscountertop.h"
Countertop::Countertop(double rotation)
		: PhysicsGameObject("countertop",QPointF(0,-5),rotation,QPointF(20,0.5),createBodyDef(b2_staticBody),QImage(":/res/counter.png")){

}

void Countertop::setBody(b2Body *newBody) {
	b2PolygonShape wall;
	wall.SetAsBox(20,0.25,b2Vec2(0,0),0);

	b2FixtureDef wallFixture;
	wallFixture.shape = &wall;
	wallFixture.isSensor = false;
	wallFixture.friction = 1;
	wallFixture.restitution = 0.1;

	newBody->CreateFixture(&wallFixture);
	PhysicsGameObject::setBody(newBody);
}
