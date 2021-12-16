/**
 * Authors - Kenzie Evans, Gavin Pease, William erignac
 *
 * A food particulate. The tank counts how
 * many of these are in it.
 */
#include "physicsfood.h"

#include <utility>

int Food::foodGenerated = 0;

/**
 * @brief Constructs the food game object
 */
Food::Food(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body) :
	PhysicsGameObject(std::move(name), position, rotation, scale, body, generateFood(), 2)
{
	auto newName = QString("food-%1").arg(foodGenerated++).toStdString();
	setName(newName);
}

/**
 * @brief Choose one of three ransom food sprites.
 */
QImage Food::generateFood()
{
	int food = ((int)rand()%3) +1;
	return QImage(QString(":/res/food_%1").arg(food));
}

/**
 * @brief Sets the body of the fish game object
 * @param newBody - the body to set it to
 */
void Food::setBody(b2Body *newBody)
{
	b2PolygonShape square;
	square.SetAsBox(0.5, 0.5);
	b2FixtureDef mainFixtureDef;
	mainFixtureDef.shape = &square;
	mainFixtureDef.density = 10;
	mainFixtureDef.friction = 0.1;
	mainFixtureDef.restitution = 0.2;
	mainFixtureDef.isSensor = false;
	newBody->CreateFixture(&mainFixtureDef);
	newBody->SetLinearDamping(2);
	PhysicsGameObject::setBody(newBody);
}

