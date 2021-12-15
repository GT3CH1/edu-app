/**
 * Authors - William Erignac
 * Last Modified - 12/15/2021
 *
 * The Animated Fish is the fish that appears in the
 * tank after its been removed from a bag. It has a
 * sinusoidal vector animation (like an infinity symbol)
 * that modifies its position, rotation, and scale if desired.
 */

#include "animatedfish.h"

/**
 * @brief Constructs an animated fish.
 * @param position Where the center of the fish's animation is. This cannot be changed afterwards.
 * @param horizontalRadius The maximum horizontal distance the fish can be from the center of its animation.
 * @param verticalRadius The maximum vertical distance the fish can be from the center of its animation.
 * @param scaleAnimation Whether to animate the fish's scale. When this is true, the fish will shrink
 * horizontally as if it were turning around.
 */
AnimatedFish::AnimatedFish(Fish::FISH_TYPE fishType, QPointF position, float horizontalRadius, float verticalRadius, bool scaleAnimation)
	: GameObject("animated fish", position, 0, QPointF(aspecRatioFromType(fishType).x*2,aspecRatioFromType(fishType).y*2),imageFromType(fishType), 4), startPos(position.x(), position.y()),
	  horizontalDistance(horizontalRadius), verticalDistance(verticalRadius), faceRight(faceDirectionFromType(fishType)), startWidth(scale.x), scaleAnimation(scaleAnimation)
{
	this->fishType = fishType;
}

/**
 * @brief Returns what kind of the 3 types of fish this is.
 */
Fish::FISH_TYPE AnimatedFish::getFishType()
{
	return fishType;
}

/**
 * @brief Animates the fish.
 * @param deltaTime The amount of time that has
 * passed between frames.
 */
void AnimatedFish::updateObject(float deltaTime)
{
	horizontalProgress += deltaTime;
	verticalProgress += deltaTime;

	if (horizontalProgress > horizontalPeriod)
		horizontalProgress -= horizontalPeriod;

	if (verticalProgress > verticalPeriod)
		verticalProgress -= verticalPeriod;

	//Make the infinity path...
	float horizontalAddition = horizontalDistance * sin(horizontalProgress / horizontalPeriod * 2 * M_PI);
	float verticalAddition = verticalDistance * sin(verticalProgress / verticalPeriod * 2 * M_PI);

	setLocation(QPointF(startPos.x + horizontalAddition, startPos.y + verticalAddition));

	//Set the scale of the fish...
	float horizontalSlope = cos(horizontalProgress / horizontalPeriod * 2 * M_PI);
	float flipMultiplier = 1;

	//If the base image faces the opposite direction the fish is moving in...
	if ((horizontalSlope > 0 && ! faceRight) || (horizontalSlope < 0 && faceRight))
		flipMultiplier = -1;

	//Add the affect that makes the fish look like it's turning in 3D if desired...
	if (scaleAnimation)
		flipMultiplier *= abs(horizontalSlope);

	setScale(b2Vec2(startWidth * flipMultiplier, scale.y));

	//Rotate the fish so that it looks somewhat in the direction that it's moving...
	float verticalSlope = (horizontalSlope / abs(horizontalSlope)) * verticalDistance * cos(verticalProgress / verticalPeriod * 2 * M_PI);
	setRotation(atan(verticalSlope) * 180 / M_PI);
}

/**
 * @brief Maps fish types to their respective sprites.
 */
QImage AnimatedFish::imageFromType(Fish::FISH_TYPE type)
{
	if ((double)rand() / (double) RAND_MAX < 0.01)
		return QImage(":/res/stinkyMonkey.png");

	switch (type) {
		case (Fish::FISH_TYPE::GOLDFISH) :
			return QImage(":/res/jim_carrey.png");
		case (Fish::FISH_TYPE::PLECO) :
			return QImage(":/res/ghanoush_fish.png");
		case (Fish::FISH_TYPE::SIMPLE) :
			return QImage(":/res/moorish_idol.png");
	}

	//Never called. Set here to prevent warnings.
	return QImage(":/res/jim_carrey.png");
}

/**
 * @brief Maps fish types to the directions they face in their sprites by default.
 */
bool AnimatedFish::faceDirectionFromType(Fish::FISH_TYPE type)
{
	switch (type) {
		case (Fish::FISH_TYPE::GOLDFISH) :
			return false;
		case (Fish::FISH_TYPE::PLECO) :
			return false;
		case (Fish::FISH_TYPE::SIMPLE) :
			return true;
	}

	//Never called. Set here to prevent warnings.
	return false;
}

/**
 * @brief Maps fish types to their aspect ratios of their respective sprites.
 */
b2Vec2 AnimatedFish::aspecRatioFromType(Fish::FISH_TYPE type)
{
	switch (type) {
		case (Fish::FISH_TYPE::GOLDFISH) :
			return b2Vec2(1, 0.531);
		case (Fish::FISH_TYPE::PLECO) :
			return b2Vec2(1,0.297);
		case (Fish::FISH_TYPE::SIMPLE) :
			return b2Vec2(0.929,1);
	}

	//Never called. Set here to prevent warnings.
	return b2Vec2(1, 0.531);
}
