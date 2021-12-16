/**
 * Authors - Kenzie Evans, Alex Richins, Gavin Pease
 */

#include "questfillbowl.h"
#include "physicgameobjectsfile.h"

/**
 * @brief Determines when the quest is passed
 */
void FillBowl::listener(const CallbackOptions &callback)
{
	auto bowl = (Bowl*)callback.getGameObject("bowl");
	int waterLevel = bowl->getWaterLevel();

	if (waterLevel > 75)
	{
		emit Quest::pass();
		Spigot* spigot = (Spigot*)callback.getGameObject("spigot");
		Clock* clock = (Clock*)callback.getGameObject("clock");
		spigot->setClickable(false);
		clock->setClickable(true);
		callback.deleteGameObject("fillBowlinstructions");
	}
}

/**
 * @brief Shows the text for the quest
 */
void FillBowl::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("fillBowlinstructions", "Lets begin by preparing your water tank!\nClick the spigot to fill the bowl\nwith tap water", QPointF(-5.1, -.5), QPointF(14, 3), 100);
	callback.addGameObject(instructionText);
}
