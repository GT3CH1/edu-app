/**
 * Authors - Kenzie Evans, Gavin Pease
 * Last Modified - 12/12/2021
 */
#include "physicsfoodcontainer.h"
#include "physicstank.h"
#include "physicsfood.h"
#include <QDebug>

// Food Container
FoodContainer::FoodContainer() :
		Dragable("foodcontainer", QPointF(-5, -4), 0, QPointF(1, 1), PhysicsGameObject::createBodyDef(b2_dynamicBody),
		         QImage(":/res/food_shaker.png"), 1)
{
	setClickable(true);
}

void FoodContainer::updateObject(float deltaTime)
{
	PhysicsGameObject::updateObject(deltaTime);

	float bodyRot = body->GetAngle();
	float absBodyRot = abs(bodyRot);

	while (absBodyRot > 2 * M_PI)
		absBodyRot -= 2 * M_PI;

	if (bodyRot < 0)
		absBodyRot = 2 * M_PI - absBodyRot;

	if ((absBodyRot > M_PI - M_PI / 4 && absBodyRot < M_PI + M_PI / 4) && spring != nullptr)
	{
		b2Vec2 velocity = body->GetLinearVelocity();
		b2Vec2 acceleration = spring->GetReactionForce(1 / callbackOptions.getDeltaTime());

		if (shakeUp && velocity.y <= 0 && lastVelocity > 0 && acceleration.y < -accelerationConstraint)
			shakeUp = false;
		else if (!shakeUp && velocity.y >= 0 && lastVelocity < 0 && acceleration.y > accelerationConstraint)
		{
			shakeUp = true;
			callbackOptions.addGameObject(new Food(
					"food",
					QPointF(getLocation().x(), getLocation().y() - 2.5),
					0,
					QPointF(1, 1),
					createBodyDef(b2_dynamicBody)
			));
		}

		lastVelocity = velocity.y;
	}
}

void FoodContainer::setBody(b2Body *newBody)
{
	b2PolygonShape square;
	square.SetAsBox(1, 2);
	b2FixtureDef mainFixtureDef;
	mainFixtureDef.shape = &square;
	mainFixtureDef.density = 10;
	mainFixtureDef.friction = 0.1;
	mainFixtureDef.restitution = 0.2;
	mainFixtureDef.isSensor = false;
	newBody->CreateFixture(&mainFixtureDef);
	newBody->SetAngularDamping(10);
	PhysicsGameObject::setBody(newBody);
}
