/**
 * Authors - Alex Richins, Kenzie Evans, Gavin Pease
 */

#include "questfilltank.h"
#include "physicgameobjectsfile.h"

/**
 * @brief Determines when the quest is passed
 */
void FillTank::listener(const CallbackOptions &callback)
{
	Tank* fishTank = (Tank*)callback.getGameObject("tank");
	int waterLevel = fishTank->getWaterLevel();

	if (waterLevel > 400)
	{
		emit Quest::pass();
		callback.deleteGameObject("fillTankinstructions");
	}
}

/**
 * @brief Shows the text for the quest
 */
void FillTank::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("fillTankinstructions", "Click the bowl to put the\ndecloronated water into the bowl", QPointF(-5, 0), QPointF(15, 3), 100);
	callback.addGameObject(instructionText);
}

