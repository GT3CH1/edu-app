/**
 * Authors - Alex Richins, Kenzie Evans, Gavin Pease, William Erignac
 */

#include "questchoosefish.h"
#include <QDebug>
#include <QPainter>

/**
 * @brief Determines when the quest is passed
 */
void ChooseFish::listener(const CallbackOptions &callback)
{
	//Get whether a fish was clicked.
	auto pleco = (Fish *) callback.getGameObject("pleco");
	auto goldfish = (Fish *) callback.getGameObject("goldfish");
	auto moorish = (Fish *) callback.getGameObject("moorish");
	bool fishSelected = (pleco->isSelected() || goldfish->isSelected() || moorish->isSelected());

	if (fishSelected)
	{
		//Remove the last quest's instructions.
		callback.deleteGameObject("ChooseFishinstructions");
		emit Quest::pass();
	}
}

/**
 * @brief Shows the text for the quest
 */
void ChooseFish::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("ChooseFishinstructions", "Please click the fish\nyou'd like to care for", QPointF(-5, -2), QPointF(12, 3), 100);
	callback.addGameObject(instructionText);
}
