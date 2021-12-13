/**
 * Authors - Kenzie Evans, Gavin Pease
 * Last Modified - 12/12/2021
 */
#include "physicsfish.h"

// Fish
Fish::Fish(std::string name, QPointF position, double rotation, QPointF scale, QImage image, FISH_TYPE fishType) :
		Dragable(name, position, rotation, scale, createBodyDef(b2_dynamicBody), image, 10) {
	setInTank(false);
	setClickable(true);
	setFishType(type);
}

bool Fish::isInTank()
{
	return inTank;
}

void Fish::onMouseClick(QPointF position)
{
	if(isClickable())
		selected = true;
	Dragable::onMouseClick(position);
}

void Fish::setInTank(bool state)
{
	inTank = state;
	if(isInTank())
		setClickable(false);
	else
		setClickable(true);
}

/**
 * @brief "Removes" the fish from bag (draws the fish without the bag)
 */
void Fish::removeFishFromBag()
{
	switch (type)
	{
		case GOLDFISH :
		{
			setGraphic(QImage(":/res/jim_carrey.png"));
			break;
		}
		case PLECO :
		{
			setGraphic(QImage(":/res/ghanoush_fish.png"));
			break;
		}
		case SIMPLE :
		{
			setGraphic(QImage(":/res/moorish_idol.png"));
			break;
		}
	}
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
void Fish::putFishInBag() {
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

void Fish::setBody(b2Body *newBody)
{
	b2PolygonShape square;
	square.SetAsBox(1,1);

	b2FixtureDef mainFixtureDef;
	mainFixtureDef.shape = &square;
	mainFixtureDef.density = 10;
	mainFixtureDef.friction = 0.1;
	mainFixtureDef.restitution = 0.2;
	mainFixtureDef.isSensor = false;

	newBody->CreateFixture(&mainFixtureDef);
	newBody->SetFixedRotation(true);
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
 * @brief Gets whether or not this fish is in a bag.
 * @return True if the fish is in a bag.
 */
bool Fish::isInBag() const
{
	return inBag;
}

/**
 * @brief Sets whether or not this fish is in a bag. Updates the sprite to match.
 * @param inBag - Flag representing if the fish is in a bag (true) or not (false).
 */
void Fish::setInBag(bool inBag)
{
	Fish::inBag = inBag;
	if(inBag)
		putFishInBag();
	else
		removeFishFromBag();
}

/**
 * @brief Sets whether or not this fish is selected.
 * @param state - Whether or not this fish is selected.
 */
void Fish::setSelected(bool state)
{
	selected = state;
}
