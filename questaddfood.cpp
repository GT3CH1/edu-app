/**
 * Authors -  Kenzie Evans, Gavin Pease, Alex Richins
 * Last Modified - 12/12/2021
 */

#include "questaddfood.h"

AddFood::AddFood(){
	callShowText = true;
}

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
	GameObject* instructionText = createTextImage("feedFishinstructions", "The fish needs to be fed, shake the fish flakes\n above the tankto give the Fish atleast 4 fish flaks", QPointF(4, 1), QPointF(15,3), 100);
	callback.addGameObject(instructionText);
}
