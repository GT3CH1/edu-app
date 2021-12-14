/**
 * Authors - Alex Richins, Kenzie Evans, Gavin Pease
 * Last Modified - 12/12/2021
 */

#include "questwait.h"

// Age Water
void Wait::listener(const CallbackOptions &callback)
{

	auto clock = (Clock *) callback.getGameObject("clock");
	auto pleco = (Fish *) callback.getGameObject("pleco");
	auto goldfish = (Fish *) callback.getGameObject("goldfish");
	auto moorish = (Fish *) callback.getGameObject("moorish");
	int time = clock->getTime();
	if (time > 24)
	{
		Bowl *bowl = (Bowl *) callback.getGameObject("bowl");
		if (bowl)
		{
			bowl->setClickable(true);
		}
		clock->setClickable(false);
		bool isAddingFishToTank = pleco != nullptr || goldfish != nullptr || moorish != nullptr;
		if (isAddingFishToTank)
		{
			auto theFish = pleco ? pleco : goldfish ? goldfish : moorish;
			theFish->setClickable(true);
		}
		emit Quest::pass();
	}



}

void Wait::reset(const CallbackOptions &callback)
{

}

void Wait::showText(const CallbackOptions &callback)
{

}
