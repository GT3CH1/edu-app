/**
 * Authors - Alex Richins, Kenzie Evans, Gavin Pease
 * Last Modified - 12/12/2021
 */

#include "questaddfish.h"
#include <QPainter>

AddFish::AddFish()
{
	callShowText = true;
}

void AddFish::listener(const CallbackOptions &callback)
{
	auto pleco = (Fish *) callback.getGameObject("pleco");
	auto goldfish = (Fish *) callback.getGameObject("goldfish");
	auto moorish = (Fish *) callback.getGameObject("moorish");
	auto clock = (Clock *) callback.getGameObject("clock");
	bool fishInTank = (pleco->isInTank() || goldfish->isInTank() || moorish->isInTank());
	auto theFish = pleco->isSelected() ? pleco : goldfish->isSelected() ? goldfish : moorish;
	if (fishInTank)
	{
		clock->setClickable(true);
		theFish->setSelected(false);
		theFish->setClickable(false);
		emit Quest::pass();
	}
}

void AddFish::reset(const CallbackOptions &callback)
{

}

void AddFish::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("addFishinstructions", "Now click the bag to cut it and\nlet the fish in the tank", QPointF(4, 1), QPointF(15,3), 100);
	callback.addGameObject(instructionText);
}
