/**
 * Authors - William Erignac, Gavin Pease
 *
 * An object that can be dragged onscreen.
 */

#include "draggable.h"
#include <QDebug>
#include <utility>

/**
 * @brief Constructs a draggable object.
 */
Draggable::Draggable(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef _b2BodyDef,
					 QImage _toRender, int layer)
	: PhysicsGameObject(std::move(name), position, rotation, scale, _b2BodyDef, std::move(_toRender), layer) {}

/**
 * @brief Instantiates an object representing the
 * mouse location and a spring to pull this object.
 * The idea is that as the mouse moves, the spring
 * pulls this object to the mouse.
 */
void Draggable::onMouseClick(QPointF mousePosition)
{
	mousePointer = new MousePointerObject(mousePosition);
	callbackOptions.addGameObject(mousePointer);
	b2Vec2 mousePositionVec(mousePosition.x(), mousePosition.y());
	b2MouseJointDef springDef;
	springDef.bodyA = mousePointer->getBody();
	springDef.bodyB = body;
	springDef.maxForce = 10000;
	springDef.target = mousePositionVec;
	springDef.dampingRatio = 0.9;
	springDef.collideConnected = false;
	spring = (b2MouseJoint *) callbackOptions.addJoint(&springDef);
}

/**
 * @brief Updates the mouse position object
 * such that the spring pulls this object
 * in the correct direction.
 */
void Draggable::onMouseHold(QPointF mousePosition)
{
	spring->SetTarget(b2Vec2(mousePosition.x(), mousePosition.y()));
}

/**
 * @brief Destroys the spring and mouse position object
 * when the mouse is released so that this object no longer follows the mouse.
 */
void Draggable::onMouseRelease(QPointF mousePosition)
{
	if (spring != nullptr)
	{
		callbackOptions.destroyJoint(spring);
		spring = nullptr;
	}

	if (mousePointer != nullptr)
	{
		callbackOptions.deleteGameObject(mousePointer->getName());
		mousePointer = nullptr;
	}
}

/**
 * @brief All a Mouse Pointer Object is a
 * static body with a position.
 */
Draggable::MousePointerObject::MousePointerObject(QPointF position)
	: PhysicsGameObject("MousePointer", position, 0, QPointF(0, 0), constructBodyDefinition(),
						QImage(":/res/stinkyMonkey.png")) {}

/**
 * @brief By default, static bodies don't update the positions of their
 * gameobjects because most static bodies don't move. This one
 * does, so it needs its position to be updated.
 */
void Draggable::MousePointerObject::updateObject(float deltaTime)
{
	position = body->GetPosition();
	rotation = body->GetAngle() * 180.0 / M_PI;
}

/**
 * @brief Constructs a simple static body.
 */
b2BodyDef Draggable::MousePointerObject::constructBodyDefinition()
{
	b2BodyDef definition;
	definition.type = b2BodyType::b2_staticBody;
	return definition;
}
