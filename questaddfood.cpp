/**
 * Authors -  Kenzie Evans, Gavin Pease, Alex Richins
 * Last Modified - 12/12/2021
 */

#include "questaddfood.h"

void AddFood::listener(const CallbackOptions &callback)
{
	Tank* fishTank = (Tank*)callback.getGameObject("tank");
	int foodGiven = fishTank->getFoodInTank();
	if (foodGiven >= 4){
		fishTank->setClickable(false);
		emit Quest::pass();
	}
}

void AddFood::reset(const CallbackOptions &callback)
{

}

void AddFood::showText(const CallbackOptions &callback)
{

}
