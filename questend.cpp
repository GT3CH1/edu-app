/**
 * Authors: Kenzie Evans
 */

#include "questend.h"
#include "physicgameobjectsfile.h"

/**
 * @brief Determines when the quest is passed
 */
void End::listener(const CallbackOptions &callback)
{
	auto startButton = (StartButton*)callback.getGameObject("startbutton");

	if (startButton->getClicked())
	{
		emit pass();
		callback.deleteGameObject("waitinstructions");
		callback.deleteGameObject("waitinstructions2");
	}
}

/**
 * @brief Shows the text for the quest
 */
void End::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("startinstructions", "CONGRATS", QPointF(0, 2), QPointF(25, 5), 100);
	callback.addGameObject(instructionText);
	GameObject* instructionText2 = createTextImage("waitinstructions2", "you can now take care of your fish for the first few days!\nclick the button below to review", QPointF(0, 0), QPointF(15, 3), 100);
	callback.addGameObject(instructionText2);
}
