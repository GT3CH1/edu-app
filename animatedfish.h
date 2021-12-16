#ifndef ANIMATEDFISH_H
#define ANIMATEDFISH_H

#include "gameobject.h"
#include "physicsfish.h"

class AnimatedFish : public GameObject
{
public:
	AnimatedFish(Fish::FISH_TYPE fishType, QPointF position, float horizontalRadius, float verticalRadius,
				 bool scaleAnimation);

	void updateObject(float deltaTime);
	AnimatedFish() = default;
	~AnimatedFish() = default;

	Fish::FISH_TYPE getFishType();

private:
	bool faceRight = false;
	bool scaleAnimation = false;
	b2Vec2 startPos = b2Vec2_zero;
	float startWidth = 1;
	float horizontalPeriod = 60;
	float verticalPeriod = 30;
	float horizontalDistance = 0;
	float verticalDistance = 0;
	float verticalProgress = 0;
	float horizontalProgress = 0;
	Fish::FISH_TYPE fishType = Fish::GOLDFISH;

	static QImage imageFromType(Fish::FISH_TYPE type);

	static bool faceDirectionFromType(Fish::FISH_TYPE type);

	static b2Vec2 aspecRatioFromType(Fish::FISH_TYPE type);
};

#endif // ANIMATEDFISH_H
