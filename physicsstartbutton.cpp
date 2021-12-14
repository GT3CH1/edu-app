#include "physicsstartbutton.h"

StartButton::StartButton()
		: PhysicsGameObject("startbutton",QPointF(0,-5),0,QPointF(6,2),createBodyDef(b2_staticBody),QImage(":/res/start_button.png")){
	clicked = false;
	setClickable(true);
}

void StartButton::setBody(b2Body *newBody) {
	b2PolygonShape wall;
	wall.SetAsBox(3,1);

	b2FixtureDef wallFixture;
	wallFixture.shape = &wall;
	wallFixture.isSensor = false;
	wallFixture.friction = 1;
	wallFixture.restitution = 0.1;

	newBody->CreateFixture(&wallFixture);
	PhysicsGameObject::setBody(newBody);
}

void StartButton::onMouseClick(QPointF position)
{
	clicked = true;
}

bool StartButton::getClicked()
{
	return clicked;
}
