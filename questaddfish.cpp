/**
 * Authors - Alex Richins, Kenzie Evans, Gavin Pease, William Erignac
 * Last Modified - 12/15/2021
 */

#include "questaddfish.h"
#include <QPainter>

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

void AddFish::reset(const CallbackOptions &callback)
{

}

void AddFish::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("addFishinstructions", "Now drag the fish below to\nput it into the tank", QPointF(-5, -1), QPointF(15,3), 100);
	callback.addGameObject(instructionText);
}
