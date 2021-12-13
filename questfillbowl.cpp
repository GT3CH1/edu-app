/**
 * Authors - Kenzie Evans, Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */

#include "questfillbowl.h"
#include "physicgameobjectsfile.h"
// FillBowl
void FillBowl::listener(const CallbackOptions &callback)
{
	Bowl* bowl = (Bowl*)callback.getGameObject("bowl");
	int waterLevel = bowl->getWaterLevel();
	/*if (waterLevel > 300){
		emit Quest::fail();
	}else */ if (waterLevel > 75){
		emit Quest::pass();
		Spigot* spigot = (Spigot*)callback.getGameObject("spigot");
		Clock* clock = (Clock*)callback.getGameObject("clock");
		spigot->setClickable(false);
		clock->setClickable(true);
	}
}

void FillBowl::reset(const CallbackOptions &callback) {}

void FillBowl::showText(const CallbackOptions &callback)
{

}
