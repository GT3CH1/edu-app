/**
 * Authors - Kenzie Evans
 *
 * The star button on the starting screen.
 */

#include "physicsstartbutton.h"

/**
 * @brief Constructs the start button game object
 */
StartButton::StartButton()
	: PhysicsGameObject("startbutton", QPointF(0, -5), 0, QPointF(6, 2), createBodyDef(b2_staticBody), QImage(":/res/start_button.png"))
{
	clicked = false;
	setClickable(true);
}

/**
 * @brief Sets the body of the start button game object
 * @param newBody - the body to be set to
 */
void StartButton::setBody(b2Body *newBody)
{
	b2PolygonShape wall;
	wall.SetAsBox(3, 1);
	b2FixtureDef wallFixture;
	wallFixture.shape = &wall;
	wallFixture.isSensor = false;
	wallFixture.friction = 1;
	wallFixture.restitution = 0.1;
	newBody->CreateFixture(&wallFixture);
	PhysicsGameObject::setBody(newBody);
}

/**
 * @brief Sets the clicked to true when clicked
 * @param position
 */
void StartButton::onMouseClick(QPointF position)
{
	clicked = true;
}

/**
 * @brief Returns if the button has been clicked
 */
bool StartButton::getClicked() const
{
	return clicked;
}
