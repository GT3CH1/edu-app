/**
 * Authors - William Erignac
 * Last Modified - 12/9/2021
 *
 * A GameObject with a physics body.
 */

#include "physicsgameobject.h"
#include <cmath>
#include <QDebug>
#include <QString>

/**
 * @brief Constructs a PhysicsGameObject.
 * @param _bodyDef The body definition should be provided
 * by the class that overrides this one.
 * NOTE: Construction does not include adding the PhysicsGameObject
 * to the physics world. The FishModel must first create a body for
 * the PhysicsGameObject using bodyDef.
 */
PhysicsGameObject::PhysicsGameObject(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef _bodyDef, QImage toRender, int layer) :
	GameObject(name, position, rotation, scale, toRender, layer)
{
	bodyDef = _bodyDef;
	isDynamic = bodyDef.type == b2_dynamicBody;
	b2Vec2 initialPos(position.x(), position.y());
}

/**
 * @brief Returns the body definition of this object.
 * NOTE: This method should only be used by the FishModel.
 */
b2BodyDef PhysicsGameObject::getBodyDef() {return bodyDef;}

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
b2Body* PhysicsGameObject::getBody(){return body;}

/**
 * @brief Returns whether this object does something when clicked on.
 */
bool PhysicsGameObject::isClickable()
{
	return clickable;
}

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
	//qDebug() << QString::fromStdString(name) << " was held at (" << position.x() << ", " << position.y() << ").";
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
	//qDebug() << QString::fromStdString(name) << " was released at (" << position.x() << ", " << position.y() << ").";
}

/**
* @brief Returns a body definition for the FishTank.
*/
b2BodyDef PhysicsGameObject::createBodyDef(b2BodyType bodyType) {
		b2BodyDef definition;
		definition.type = bodyType;
		return definition;
}

void PhysicsGameObject::setRotation(double rotation)
{
	GameObject::setRotation(rotation);
	body->SetFixedRotation(true);
	body->SetTransform(position,rotation);
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

void PhysicsGameObject::onCollisionEnter(b2Contact *collision, bool isA, PhysicsGameObject *other)
{
	//qDebug() << "Entered a Collision with: " << QString::fromStdString(other->getName());
}
void PhysicsGameObject::onCollisionStay(b2Contact *collision, bool isA, PhysicsGameObject *other)
{
	//qDebug() << "Stayed a Collision with: " << QString::fromStdString(other->getName());
}
void PhysicsGameObject::onCollisionExit(PhysicsGameObject *other)
{
	//qDebug() << "Exited a Collision with: " << QString::fromStdString(other->getName());
}

void PhysicsGameObject::onSensorEnter(b2Contact *collision, bool isA, PhysicsGameObject *other)
{
	//qDebug() << "Entered a Sense with: " << QString::fromStdString(other->getName());
}
void PhysicsGameObject::onSensorStay(b2Contact *collision, bool isA, PhysicsGameObject *other)
{
	//qDebug() << "Stayed a Sense with: " << QString::fromStdString(other->getName());
}
void PhysicsGameObject::onSensorExit(PhysicsGameObject *other)
{
	//qDebug() << "Exit a Sense with: " << QString::fromStdString(other->getName());
}

