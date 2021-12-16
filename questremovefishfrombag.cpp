/**
 * Authors - Gavin Pease, Alex Richins, William Erignac
 * Last Modified - 12/13/2021
 */

#include "questremovefishfrombag.h"

RemoveFishFromBag::RemoveFishFromBag(){
	callShowText = true;
}
void RemoveFishFromBag::listener(const CallbackOptions &callback)
{
	auto tank = (Tank*) callback.getGameObject("tank");

	//Get which fish was put into the tank earlier.
	auto pleco = (Fish *) callback.getGameObject("pleco");
	auto goldfish = (Fish *) callback.getGameObject("goldfish");
	auto moorish = (Fish *) callback.getGameObject("moorish");
	auto theFish = pleco ? pleco : goldfish ? goldfish : moorish;

	//Get the type of fish selected by the player.
	Fish::FISH_TYPE type = pleco ? Fish::FISH_TYPE::PLECO : goldfish ? Fish::FISH_TYPE::GOLDFISH : Fish::FISH_TYPE::SIMPLE;

	//Get whether the fish has been clicked yet.
	bool fishSelected = theFish->isSelected();
	if (fishSelected)
	{
		//Destroy the fish in the bag and replace it with the animated fish.
		callback.deleteGameObject(theFish->getName());
		AnimatedFish* unbaggedFish = new AnimatedFish(type, tank->getLocation(), 1.5, 0.5, true);
		//Tell the model about the new fish.
		emit fishRemovedFromBag(unbaggedFish);
		callback.addGameObject(unbaggedFish);
		emit Quest::pass();
		callback.deleteGameObject("unBagFishinstructions");
	}
}

void RemoveFishFromBag::reset(const CallbackOptions &callback)
{

}

void RemoveFishFromBag::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("unBagFishinstructions", "Now that the fish has acclimated to the tank\nclick the bag to release the fish into the tank", QPointF(4, 1.5), QPointF(15,3), 100);
	callback.addGameObject(instructionText);
}
