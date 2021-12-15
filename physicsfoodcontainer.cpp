/**
 * Authors - Kenzie Evans, Gavin Pease, William Erignac
 * Last Modified - 12/12/2021
 *
 * A food dispenser that must be shaken to dispense food.
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

	//Clamp the rotation of this container from 0 to 2PI.
	float bodyRot = body->GetAngle();
	float absBodyRot = abs(bodyRot);

	while (absBodyRot > 2 * M_PI)
		absBodyRot -= 2 * M_PI;

	if (bodyRot < 0)
		absBodyRot = 2 * M_PI - absBodyRot;

	//If the container is facing down and is being held, it may drop food particles.
	if ((absBodyRot > M_PI - M_PI / 4 && absBodyRot < M_PI + M_PI / 4) && spring != nullptr)
	{
		b2Vec2 velocity = body->GetLinearVelocity();
		b2Vec2 acceleration = spring->GetReactionForce(1 / callbackOptions.getDeltaTime());

		//If the cansiter is starting to move down with enough force while being held, change its state.
		if (shakeUp && velocity.y <= 0 && lastVelocity > 0 && acceleration.y < -accelerationConstraint)
			shakeUp = false;
		/*
		 * If the cansiter is starting to move up with enough force while being held, change its state
		 * and spawn a food particle.
		 */
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
	square.SetAsBox(1, 1.74);
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
