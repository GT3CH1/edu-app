/**
 * Authors - Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */
#include "physicsclock.h"
// Clock
Clock::Clock() :
		PhysicsGameObject("clock", QPointF(-8,5), 0, QPointF(2,2), PhysicsGameObject::createBodyDef(b2_staticBody), QImage(":/res/clock.png"))
{
	time = 0;
	baseClock = graphic;
}

int Clock::getTime()
{
	return time;
}

void Clock::setTime(int newTime)
{
	time = newTime;
	drawClock();
}

void Clock::addTime(){
	time++;
	drawClock();
}

void Clock::setBody(b2Body *newBody)
{
	// Make the sensor...
	b2PolygonShape sensorShape;
	sensorShape.SetAsBox(1, 1);

	b2FixtureDef hitBoxDefinition;
	hitBoxDefinition.shape = &sensorShape;
	hitBoxDefinition.isSensor = true;

	newBody->CreateFixture(&hitBoxDefinition);
	PhysicsGameObject::setBody(newBody);
}

void Clock::onMouseHold(QPointF position){
	addTime();
}

void Clock::drawClock(){
	QTransform rotationT;
	rotationT.rotate(time*30);
	graphic = baseClock.transformed(rotationT);
}
