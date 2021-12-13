/**
 * Authors - Alex Richins, Kenzie Evans, Gavin Pease
 * Last Modified - 12/12/2021
 */

#include "questfilltank.h"
#include "physicgameobjectsfile.h"
// FillTank
void FillTank::listener(const CallbackOptions &callback)
{
	Tank* fishTank = (Tank*)callback.getGameObject("tank");
	int waterLevel = fishTank->getWaterLevel();
	/*if (waterLevel > 300){
		emit Quest::fail();
	}else */ if (waterLevel > 400){
		emit Quest::pass();
	}
}

void FillTank::reset(const CallbackOptions &callback)
{

}

void FillTank::showText(const CallbackOptions &callback)
{

}
