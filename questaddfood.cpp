/**
 * Authors -  Kenzie Evans, Gavin Pease, Alex Richins
 */

#include "questaddfood.h"

/**
 * @brief Determines when the quest is passed
 */
void AddFood::listener(const CallbackOptions &callback)
{
	Tank* fishTank = (Tank*)callback.getGameObject("tank");
	int foodGiven = fishTank->getFoodInTank();

	if (foodGiven >= 4)
	{
		fishTank->setClickable(false);
		callback.deleteGameObject("feedFishinstructions");
		emit Quest::pass();
	}
}


/**
 * @brief Shows the text for the quest
 */
void AddFood::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("feedFishinstructions", "The fish needs to be fed, shake the\nfish flakes above the tank upside down\nto give the Fish atleast 4 fish flaks", QPointF(-5, 0), QPointF(15, 3), 100);
	callback.addGameObject(instructionText);
}
