#ifndef ANIMATEDFISH_H
#define ANIMATEDFISH_H

#include "gameobject.h"
#include "physicsfish.h"

class AnimatedFish : public GameObject
{
public:
	AnimatedFish(Fish::FISH_TYPE fishType, QPointF position, float horizontalRadius, float verticalRadius, bool scaleAnimation);
	void updateObject(float deltaTime);
	Fish::FISH_TYPE getFishType();
private:
	const bool faceRight;
	const bool scaleAnimation;
	const b2Vec2 startPos;
	const float startWidth;
	const float horizontalPeriod = 60;
	const float verticalPeriod = 30;
	const float horizontalDistance;
	const float verticalDistance;
	float verticalProgress = 0;
	float horizontalProgress = 0;
	Fish::FISH_TYPE fishType;

	static QImage imageFromType(Fish::FISH_TYPE type);
	static bool faceDirectionFromType(Fish::FISH_TYPE type);
	static b2Vec2 aspecRatioFromType(Fish::FISH_TYPE type);
};

#endif // ANIMATEDFISH_H
