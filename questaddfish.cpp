/**
 * Authors - Alex Richins, Kenzie Evans, Gavin Pease, William Erignac
 */

#include "questaddfish.h"
#include <QPainter>

/**
 * @brief Determines when the quest is passed
 */
void AddFish::listener(const CallbackOptions &callback)
{
	auto clock = (Clock *) callback.getGameObject("clock");
	//Get the fish dropped in the tank.
	auto pleco = (Fish *) callback.getGameObject("pleco");
	auto goldfish = (Fish *) callback.getGameObject("goldfish");
	auto moorish = (Fish *) callback.getGameObject("moorish");
	auto theFish = pleco->isInTank() ? pleco : goldfish->isInTank() ? goldfish : moorish;
	//Get whether the player has selected a fish by putting it in the tank.
	bool fishInTank = (pleco->isInTank() || goldfish->isInTank() || moorish->isInTank());

	if (fishInTank)
	{
		//Next step is to fast-forward time.
		clock->setClickable(true);
		theFish->setSelected(false);
		theFish->setClickable(false);

		//Get rid of the extranous fish.
		if (pleco->isInTank())
		{
			callback.deleteGameObject(goldfish->getName());
			callback.deleteGameObject(moorish->getName());
		}

		else if (goldfish->isInTank())
		{
			callback.deleteGameObject(pleco->getName());
			callback.deleteGameObject(moorish->getName());
		}

		else if (moorish->isInTank())
		{
			callback.deleteGameObject(goldfish->getName());
			callback.deleteGameObject(pleco->getName());
		}

		callback.deleteGameObject("addFishinstructions");
		emit Quest::pass();
	}
}

/**
 * @brief Shows the text for the quest
 */
void AddFish::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("addFishinstructions", "Now drag and drop the fish into the tank \n to begin the acclimation process.", QPointF(4, 1), QPointF(15, 3), 100);
	callback.addGameObject(instructionText);
}
