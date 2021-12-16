/**
 * Authors -  Kenzie Evans, Gavin Pease, Alex Richins
 * Last Modified - 12/15/2021
 */

#include "questaddfood.h"

void AddFood::listener(const CallbackOptions &callback)
{
	Tank* fishTank = (Tank*)callback.getGameObject("tank");
	int foodGiven = fishTank->getFoodInTank();
	if (foodGiven >= 4){
		fishTank->setClickable(false);
		callback.deleteGameObject("feedFishinstructions");
		emit Quest::pass();
	}
}

void AddFood::reset(const CallbackOptions &callback)
{

}

void AddFood::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("feedFishinstructions", "The fish needs to be fed, shake the\nfish flakes above the tank upside down\nto give the Fish atleast 4 fish flaks", QPointF(-5, 0), QPointF(15,3), 100);
	callback.addGameObject(instructionText);
}
