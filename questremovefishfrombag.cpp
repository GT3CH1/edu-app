/**
 * Authors - Gavin Pease, Alex Richins
 * Last Modified - 12/12/2021
 */

#include "questremovefishfrombag.h"

void RemoveFishFromBag::listener(const CallbackOptions &callback)
{
	auto pleco = (Fish *) callback.getGameObject("pleco");
	auto goldfish = (Fish *) callback.getGameObject("goldfish");
	auto moorish = (Fish *) callback.getGameObject("moorish");
	bool fishSelected = (pleco->isSelected() || goldfish->isSelected() || moorish->isSelected());
	auto theFish = pleco->isSelected() ? pleco : goldfish->isSelected() ? goldfish : moorish;
	if (fishSelected)
	{
		theFish->setInBag(false);
		if(theFish->getName() == "pleco" || theFish->getName() == "goldfish")
			theFish->setScale(b2Vec2(2,1));
		emit fishRemovedFromBag(theFish);
		emit Quest::pass();
	}
}

void RemoveFishFromBag::reset(const CallbackOptions &callback)
{

}

void RemoveFishFromBag::showText(const CallbackOptions &callback)
{

}
