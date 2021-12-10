/**
 * Authors - William Erignac
 * Last Modified - 12/9/2021
 *
 * A PhysicsGameObject that does more complex collision handeling.
 */

#include "advancedphysicsgameobject.h"
#include <QDebug>

AdvancedPhysicsGameObject::AdvancedPhysicsGameObject(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef _b2BodyDef, QImage toRender)
	: PhysicsGameObject(name, position, rotation, scale, _b2BodyDef, toRender)
{}

/**
 * @brief Checks the exit collision triggers and
 * @param deltaTime
 */
void AdvancedPhysicsGameObject::updateObject(float deltaTime)
{
	PhysicsGameObject::updateObject(deltaTime);

	std::function<void*(std::string)> getGameObject = callbackOptions.getGameObject;

	//If we didn't collide with objects we collided with last frame, they left us.
	for(std::string name : lastContacts)
	{
		if(contacts.count(name) == 0)
		{
			PhysicsGameObject* object = (PhysicsGameObject*) getGameObject(name);
			onCollisionExit(object);
		}
	}

	//If we didn't sense objects we sensed last frame, they left us.
	for(std::string name : lastSensorContacts)
	{
		if(sensorContacts.count(name) == 0)
		{
			PhysicsGameObject* object = (PhysicsGameObject*) getGameObject(name);
			onSensorExit(object);
		}
	}

	lastContacts = contacts;
	lastSensorContacts = sensorContacts;
	contacts.clear();
	sensorContacts.clear();
}

/**
 * @brief Determines the collision state between this object and other.
 */
void AdvancedPhysicsGameObject::onCollision(b2Contact* collision, bool isA, PhysicsGameObject* other)
{
	std::string name = other->getName();
	contacts.insert(name);

	if(lastContacts.count(name) == 0)
		onCollisionEnter(collision, isA, other);
	else
		onCollisionStay(collision, isA, other);
}

/**
 * @brief Determines the sensor state between this object and other.
 */
void AdvancedPhysicsGameObject::onSensor(b2Contact* collision, bool isA, PhysicsGameObject* other)
{
	std::string name = other->getName();
	sensorContacts.insert(name);

	if(lastSensorContacts.count(name) == 0)
		onSensorEnter(collision, isA, other);
	else
		onSensorStay(collision, isA, other);
}

void AdvancedPhysicsGameObject::onCollisionEnter(b2Contact *collision, bool isA, PhysicsGameObject *other)
{
	//qDebug() << "Entered a Collision with: " << QString::fromStdString(other->getName());
}
void AdvancedPhysicsGameObject::onCollisionStay(b2Contact *collision, bool isA, PhysicsGameObject *other)
{
	//qDebug() << "Stayed a Collision with: " << QString::fromStdString(other->getName());
}
void AdvancedPhysicsGameObject::onCollisionExit(PhysicsGameObject *other)
{
	//qDebug() << "Exited a Collision with: " << QString::fromStdString(other->getName());
}

void AdvancedPhysicsGameObject::onSensorEnter(b2Contact *collision, bool isA, PhysicsGameObject *other)
{
	//qDebug() << "Entered a Sense with: " << QString::fromStdString(other->getName());
}
void AdvancedPhysicsGameObject::onSensorStay(b2Contact *collision, bool isA, PhysicsGameObject *other)
{
	//qDebug() << "Stayed a Sense with: " << QString::fromStdString(other->getName());
}
void AdvancedPhysicsGameObject::onSensorExit(PhysicsGameObject *other)
{
	//qDebug() << "Exit a Sense with: " << QString::fromStdString(other->getName());
}
