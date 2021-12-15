/**
 * Authors - Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 *
 * An object that speeds up the passing
 * of time when clicked and held.
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
	//The sky will be turned by the clock, so we need a reference to it.
	sky = (GameObject*) callbackOptions.getGameObject("sky");

	//A hand is needed to display the hour, so it is instantiated.
	hourHand = new GameObject("hour hand", QPointF(position.x, position.y), rotation, QPointF(scale.x, scale.y),QImage(":/res/hour_hand.png"), 2);
	callbackOptions.addGameObject(hourHand);

	//A hand is needed to display the minute, so it is instantiated.
	minuteHand = new GameObject("minute hand", QPointF(position.x, position.y), rotation, QPointF(scale.x, scale.y),QImage(":/res/minute_hand.png"), 2);
	callbackOptions.addGameObject(minuteHand);
}

/**
 * @brief Returns the hour of the clock.
 */
int Clock::getTime()
{
	return time;
}

/**
 * @brief Sets the time of the clock to the provided hour.
 */
void Clock::setTime(int newTime)
{
	time = newTime;
	drawClock();
}

/**
 * @brief Increments the clock. This assumes that
 * this method is only called at most once per frame.
 */
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
	//Make time fast-forward as the clock is held.
	addTime();
}

/**
 * @brief Updates the rotations of the objects
 * that illustrate the time of this clock.
 */
void Clock::drawClock(){
	QTransform rotationT;
	hourHand->setRotation(-time/12*360);
	minuteHand->setRotation(-time*360);
	if (sky != nullptr)
		sky->setRotation(180 - time/24*360);
}
