/**
 * Authors - Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */
#include "physicsclock.h"
#include <QDebug>
// Clock
Clock::Clock() :
		PhysicsGameObject("clock", QPointF(-8,5), 0, QPointF(2,2), PhysicsGameObject::createBodyDef(b2_staticBody), QImage(":/res/clock.png"))
{
	time = 0;
}

void Clock::start()
{
	sky = (GameObject*) callbackOptions.getGameObject("sky");

	hourHand = new GameObject("hour hand", QPointF(position.x, position.y), rotation, QPointF(scale.x, scale.y),QImage(":/res/hour_hand.png"), 2);
	callbackOptions.addGameObject(hourHand);

	minuteHand = new GameObject("minute hand", QPointF(position.x, position.y), rotation, QPointF(scale.x, scale.y),QImage(":/res/minute_hand.png"), 2);
	callbackOptions.addGameObject(minuteHand);
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
	time += clockRate * callbackOptions.getDeltaTime();
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
	hourHand->setRotation(-time/12*360);
	minuteHand->setRotation(-time*360);
	if (sky != nullptr)
		sky->setRotation(180 - time/24*360);
}
