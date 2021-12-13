/**
 * Authors - Kenzie Evans, Gavin Pease
 * Last Modified - 12/12/2021
 */
#include "physicsfood.h"
int Food::foodGenerated = 0;
// Food
Food::Food(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body) :
		PhysicsGameObject(name, position, rotation, scale, body, generateFood(),2)
{
	auto newName = QString("food-%1").arg(foodGenerated++).toStdString();
	setName(newName);
}
QImage Food::generateFood()
{
	int food = ((int)rand()%3) +1;
	return QImage(QString(":/res/food_%1").arg(food));
}

void Food::setBody(b2Body *newBody)
{
	b2PolygonShape square;
	square.SetAsBox(0.5,0.5);

	b2FixtureDef mainFixtureDef;
	mainFixtureDef.shape = &square;
	mainFixtureDef.density = 10;
	mainFixtureDef.friction = 0.1;
	mainFixtureDef.restitution = 0.2;
	mainFixtureDef.isSensor = false;

	newBody->CreateFixture(&mainFixtureDef);

	PhysicsGameObject::setBody(newBody);
}

