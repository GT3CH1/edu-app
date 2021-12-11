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
bool PhysicsGameObject::getIsClickable()
{
	return clickable;
}

/**
 * @brief Aligns the object's position and rotation
 * to the position and rotation of its body in the physics world.
 *
 * NOTE: If you wish to override this, make sure to always call
 * PhysicsGameObject::updateObject(deltaTime) at the start of
 * the method.
 */
void PhysicsGameObject::updateObject(float deltaTime)
{
	if (isDynamic)
	{
		position = body->GetPosition();
		rotation = body->GetAngle() * 180.0/M_PI;
	}
}

/**
 * @brief Is triggered when a non-sensor
 * fixture of this object's body collides with another fixture.
 * Override this to do something on collisions.
 * @param isA b2Contacts have two fixtures, A and B. isA
 * is true when the fixture corresponding to this object is
 * the A fixture.
 *
 * NOTE: This method is called anytime there's a new collision
 * between this object and another, or if there is a maintained collision.
 */
void PhysicsGameObject::onCollision(b2Contact* collision, bool isA, PhysicsGameObject* other) {}

/**
 * @brief Is triggered when a sensor
 * fixture of this object's body sense another fixture.
 * @param isA b2Contacts have two fixtures, A and B. isA
 * is true when the fixture corresponding to this object is
 * the A fixture.
 *
 * NOTE: This method is called anytime there's a fixture
 * in one of this object's sensors.
 */
void PhysicsGameObject::onSensor(b2Contact* collision, bool isA, PhysicsGameObject* other) {}

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
