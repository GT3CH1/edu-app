/**
 * Authors - Kenzie Evans, Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */
#include "questfillbowl.h"
#include "physicgameobjectsfile.h"

FillBowl::FillBowl(){
	callShowText = true;
}
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
		callback.deleteGameObject("fillBowlinstructions");
	}
}

void FillBowl::reset(const CallbackOptions &callback) {}

void FillBowl::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("fillBowlinstructions", "Click the spigot to fill the bowl with tap water", QPointF(4, 1), QPointF(15,3), 100);
	callback.addGameObject(instructionText);
}
