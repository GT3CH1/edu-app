/**
 * Authors - William Erignac
 *
 * A GameObject with a physics body.
 */

#include "physicsgameobject.h"
#include <cmath>
#include <QDebug>
#include <QString>
#include <utility>

/**
 * @brief Constructs a PhysicsGameObject.
 * @param _bodyDef The body definition should be provided
 * by the class that overrides this one.
 * NOTE: Construction does not include adding the PhysicsGameObject
 * to the physics world. The FishModel must first create a body for
 * the PhysicsGameObject using bodyDef.
 */
PhysicsGameObject::PhysicsGameObject(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef _bodyDef, QImage toRender, int layer) :
	GameObject(std::move(name), position, rotation, scale, std::move(toRender), layer)
{
	bodyDef = _bodyDef;
	isDynamic = bodyDef.type == b2_dynamicBody;
}

/**
 * @brief Returns the body definition of this object.
 * NOTE: This method should only be used by the FishModel.
 */
b2BodyDef PhysicsGameObject::getBodyDef()
{
	return bodyDef;
}

/**
 * @brief Sets the body of this object to the provided body.
 * NOTE: Bodies are not created by PhysicsGameObjects; the
 * FishModel passes a body to the PhysicsGameObject.
 *
 * NOTE: This method should only be called by the FishModel.
 *
 * NOTE: Override this method to add fixtures (hitboxes) to
 * the PhysicsGameObject (see FishTank for an example).
 * When overriding, always call PhysicsGameObject::setBody(newBody)
 * at the end of the method.
 */
void PhysicsGameObject::setBody(b2Body* newBody)
{
	body = newBody;
	body->SetTransform(position, rotation * M_PI/180.0);
	body->SetUserData(this);
}

/**
 * @brief Returns the body of this object.
 */
b2Body* PhysicsGameObject::getBody()
{
	return body;
}

/**
 * @brief Returns whether this object does something when clicked on.
 */
bool PhysicsGameObject::isClickable() const
{
	return clickable;
}

/**
 * @brief Sets whether this object does something when clicked on.
 */
void PhysicsGameObject::setClickable(bool setClickable)
{
	clickable = setClickable;
}

/**
 * @brief Is triggered when one of this
 * object's fixtures are clicked (doesn't matter
 * if it's a sensor).
 * @param position The position that the object was clicked at.
 */
void PhysicsGameObject::onMouseClick(QPointF mousePosition)
{
	qDebug() << QString::fromStdString(name) << " was clicked at (" << mousePosition.x() << ", " << mousePosition.y() << ").";
}

/**
 * @brief Is triggered when the object was clicked
 * and the mouse is still held.
 * @param position The position that the mouse is being held.
 *
 * NOTE: The mouse doesn't have to be on one of the
 * fixtures of the object for this to be called (click,
 * hold, move mouse off object still calls this method).
 */
void PhysicsGameObject::onMouseHold(QPointF mousePosition)
{
}

/**
 * @brief Is triggered when the object was clicked
 * and the mouse is released.
 * @param position The position that the mouse was released at.
 *
 * NOTE: The mouse doesn't have to be on one of the fixtures
 * of the object for this to be called.
 */
void PhysicsGameObject::onMouseRelease(QPointF mousePosition)
{
}

/**
* @brief Returns a body definition for the FishTank.
*/
b2BodyDef PhysicsGameObject::createBodyDef(b2BodyType bodyType)
{
	b2BodyDef definition;
	definition.type = bodyType;
	return definition;
}

/**
 * @brief Sets the rotation of the game object
 * @param rotation
 */
void PhysicsGameObject::setRotation(double rotation)
{
	GameObject::setRotation(rotation);
	body->SetFixedRotation(true);
	body->SetTransform(position, rotation);
}

/**
 * @brief Checks the exit collision triggers and
 * @param deltaTime
 */
void PhysicsGameObject::updateObject(float deltaTime)
{
	if (isDynamic)
	{
		position = body->GetPosition();
		rotation = body->GetAngle() * 180.0/M_PI;
	}

	std::function<void*(std::string)> getGameObject = callbackOptions.getGameObject;

	//If we didn't collide with objects we collided with last frame, they left us.
	for(const auto& name : lastContacts)
	{
		if(contacts.count(name) == 0)
		{
			PhysicsGameObject* object = (PhysicsGameObject*) getGameObject(name);

			if (object != nullptr)
				onCollisionExit(object);
		}
	}

	//If we didn't sense objects we sensed last frame, they left us.
	for(auto &name : lastSensorContacts)
	{
		if(sensorContacts.count(name) == 0)
		{
			PhysicsGameObject* object = (PhysicsGameObject*) getGameObject(name);

			if (object != nullptr)
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
void PhysicsGameObject::onCollision(b2Contact* collision, bool isA, PhysicsGameObject* other)
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
void PhysicsGameObject::onSensor(b2Contact* collision, bool isA, PhysicsGameObject* other)
{
	std::string name = other->getName();
	sensorContacts.insert(name);

	if(lastSensorContacts.count(name) == 0)
		onSensorEnter(collision, isA, other);

	else
		onSensorStay(collision, isA, other);
}

/**
 * @brief Called whenever a new collision occurs between this object and another.
 * Override this to do things on collisions.
 * @param isA Whether this is the A or B object in the collision parameter.
 * @param other The object that collided with this object.
 */
void PhysicsGameObject::onCollisionEnter(b2Contact *collision, bool isA, PhysicsGameObject *other)
{
}

/**
 * @brief Called whilst an object is resting on this one.
 * Override this to do things on collisions.
 * @param isA Whether this is the A or B object in the collision parameter.
 * @param other The object that is resting on this object.
 */
void PhysicsGameObject::onCollisionStay(b2Contact *collision, bool isA, PhysicsGameObject *other)
{
}

/**
 * @brief Called whenever an object stops contact with (leaves) this object.
 * Override this to do things on collisions.
 * @param other The object left this object.
 */
void PhysicsGameObject::onCollisionExit(PhysicsGameObject *other)
{
}

/**
 * @brief Called whenever an object just enters one of this object's sensors.
 * Override this to do things on senses.
 * @param isA Whether this is the A or B object in the collision parameter.
 * @param other The object that this was sensed.
 */
void PhysicsGameObject::onSensorEnter(b2Contact *collision, bool isA, PhysicsGameObject *other)
{
}

/**
 * @brief Called whenever an object stays in one of this object's sensors.
 * Override this to do things on senses.
 * @param isA Whether this is the A or B object in the collision parameter.
 * @param other The object that is still in this object's sensor.
 */
void PhysicsGameObject::onSensorStay(b2Contact *collision, bool isA, PhysicsGameObject *other)
{
}

/**
 * @brief Called whenever an object leaves this object's sensors.
 * Override this to do things on senses.
 * @param isA Whether this is the A or B object in the collision parameter.
 * @param other The object that left this object's sensors.
 */
void PhysicsGameObject::onSensorExit(PhysicsGameObject *other)
{
}

