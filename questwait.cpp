/**
 * Authors - Alex Richins, Kenzie Evans, Gavin Pease
 * Last Modified - 12/12/2021
 */

#include "questwait.h"

Wait::Wait(){
	callShowText = true;
}
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
		callback.deleteGameObject("waitinstructions");
		emit Quest::pass();
	}



}

void Wait::reset(const CallbackOptions &callback)
{

}

void Wait::showText(const CallbackOptions &callback)
{
	Bowl *bowl = (Bowl *) callback.getGameObject("bowl");
	if (bowl)
	{
		GameObject* instructionText = createTextImage("waitinstructions", "The water needs to wait a day to allow the chlorine to evaporate.\nClick the clock to speed up time", QPointF(4, 1), QPointF(15,3), 100);
		callback.addGameObject(instructionText);
	}

	auto pleco = (Fish *) callback.getGameObject("pleco");
	auto goldfish = (Fish *) callback.getGameObject("goldfish");
	auto moorish = (Fish *) callback.getGameObject("moorish");
	if (pleco != nullptr || goldfish != nullptr || moorish != nullptr)
	{
		GameObject* instructionText = createTextImage("waitinstructions", "The fish needs to have time to adjust to it's new climate slowly over a day.\nCLick the clock to speed up time", QPointF(4, 1), QPointF(15,3), 100);
		callback.addGameObject(instructionText);
	}
}
