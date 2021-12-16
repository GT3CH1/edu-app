/**
 * Authors - Kenzie Evans, Gavin Pease, William Erignac
 * Last Modified - 12/12/2021
 *
 * The fish in a bag.
 */
#include "physicsfish.h"

#include <utility>

/**
 * @brief Constructs the fish game object
 * @param name - name of the fish
 * @param position - position of the fish in the world
 * @param rotation - rotation of the fish
 * @param scale - scale of the fish
 * @param image - image used for the fish
 * @param fishType - the type of fish
 */
Fish::Fish(std::string name, QPointF position, double rotation, QPointF scale, QImage image, FISH_TYPE fishType) :
	Draggable(std::move(name), position, rotation, scale, createBodyDef(b2_dynamicBody), std::move(image), 10)
{
	setInTank(false);
	setClickable(true);
	setFishType(fishType);
}

/**
 * @brief Returns if the fish is in the tank
 */
bool Fish::isInTank() const
{
	return inTank;
}

/**
 * @brief Drags the fish if the fish is clickable
 * @param position - the position that the mouse is clicked
 */
void Fish::onMouseClick(QPointF position)
{
	if(isClickable())
		selected = true;

	Draggable::onMouseClick(position);
}

/**
 * @brief Sets the fish in the tank
 * @param state - current state of the fish
 */
void Fish::setInTank(bool state)
{
	inTank = state;
	setClickable(!state);
}

/**
 * @brief Sets the fish type, and updates the image.
 * @param fishType - The type of fish we want to draw.
 */
void Fish::setFishType(Fish::FISH_TYPE fishType)
{
	type = fishType;
	putFishInBag();
}

/**
 * @brief "Puts" the fish in the bag (draws fish in bag)
 */
void Fish::putFishInBag()
{
	switch (type)
	{
		case GOLDFISH :
		{
			graphic = QImage(":/res/jim_carrey_bag.png");
			break;
		}

		case PLECO :
		{
			graphic = QImage(":/res/ghanoush_fish_bag.png");
			break;
		}

		case SIMPLE :
		{
			graphic = QImage(":/res/moorish_idol_bag.png");
			break;
		}
	}
}

/**
 * @brief Sets the body of the game object
 * @param newBody - the body to set it to
 */
void Fish::setBody(b2Body *newBody)
{
	b2PolygonShape square;
	square.SetAsBox(1, 1);
	b2FixtureDef mainFixtureDef;
	mainFixtureDef.shape = &square;
	mainFixtureDef.density = 10;
	mainFixtureDef.friction = 0.1;
	mainFixtureDef.restitution = 0.2;
	mainFixtureDef.isSensor = false;
	newBody->CreateFixture(&mainFixtureDef);
	newBody->SetFixedRotation(true);
	newBody->SetLinearDamping(0.75);
	PhysicsGameObject::setBody(newBody);
}

/**
 * @brief Gets whether or not this fish was selected.
 * @return - True if selected, false otherwise
 */
bool Fish::isSelected() const
{
	return selected;
}

/**
 * @brief Sets whether or not this fish is selected.
 * @param state - Whether or not this fish is selected.
 */
void Fish::setSelected(bool state)
{
	selected = state;
}
