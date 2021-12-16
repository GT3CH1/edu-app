/**
 * Authors - Alex Richins, Kenzie Evans, Gavin Pease
 */

#include "questwait.h"

/**
 * @brief Determines when the quest is passed
 */
void Wait::listener(const CallbackOptions &callback)
{
	auto clock = (Clock *) callback.getGameObject("clock");
	auto pleco = (Fish *) callback.getGameObject("pleco");
	auto goldfish = (Fish *) callback.getGameObject("goldfish");
	auto moorish = (Fish *) callback.getGameObject("moorish");
	int time = clock->getTime();

	if (time > 23)
	{
		Bowl *bowl = (Bowl *) callback.getGameObject("bowl");

		if (bowl)
			bowl->setClickable(true);

		clock->setClickable(false);
		bool isAddingFishToTank = pleco != nullptr || goldfish != nullptr || moorish != nullptr;

		if (isAddingFishToTank)
		{
			auto theFish = pleco ? pleco : goldfish ? goldfish : moorish;
			theFish->setClickable(true);
		}

		callback.deleteGameObject("waitinstructions");
		callback.deleteGameObject("waitinstructions2");
		emit Quest::pass();
	}
}

/**
 * @brief Shows the text for the quest
 */
void Wait::showText(const CallbackOptions &callback)
{
	Bowl *bowl = (Bowl *) callback.getGameObject("bowl");

	if (bowl)
	{
		GameObject* instructionText = createTextImage("waitinstructions", "The water needs to wait a day to allow\nthe chlorine to evaporate.\nOtherwise your fishes gills\nwill be burned. ", QPointF(-5, -0.5), QPointF(15, 4), 100);
		callback.addGameObject(instructionText);
	}

	auto pleco = (Fish *) callback.getGameObject("pleco");
	auto goldfish = (Fish *) callback.getGameObject("goldfish");
	auto moorish = (Fish *) callback.getGameObject("moorish");

	if (pleco != nullptr || goldfish != nullptr || moorish != nullptr)
	{
		GameObject* instructionText = createTextImage("waitinstructions", "The fish needs to have time to adjust to\nit's new climate slowly over the \ncourse of about an hour.", QPointF(-5, 0), QPointF(15, 3), 100);
		callback.addGameObject(instructionText);
	}

	GameObject* instructionText2 = createTextImage("waitinstructions2", "Click the clock to speed up time", QPointF(-5, 3.5), QPointF(15, 1.5), 100);
	callback.addGameObject(instructionText2);
}
