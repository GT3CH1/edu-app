/**
 * Authors - Gavin Pease, Alex Richins
 * Last Modified - 12/12/2021
 */

#include "questremovefishfrombag.h"

RemoveFishFromBag::RemoveFishFromBag(){
	callShowText = true;
}
void RemoveFishFromBag::listener(const CallbackOptions &callback)
{
	auto pleco = (Fish *) callback.getGameObject("pleco");
	auto goldfish = (Fish *) callback.getGameObject("goldfish");
	auto moorish = (Fish *) callback.getGameObject("moorish");
	auto theFish = pleco ? pleco : goldfish ? goldfish : moorish;
	bool fishSelected = theFish->isSelected();
	if (fishSelected)
	{
		theFish->setInBag(false);
		if(theFish->getName() == "pleco" || theFish->getName() == "goldfish")
			theFish->setScale(b2Vec2(2,1));
		emit fishRemovedFromBag(theFish);
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
