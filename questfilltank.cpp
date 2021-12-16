/**
 * Authors - Alex Richins, Kenzie Evans, Gavin Pease
 * Last Modified - 12/15/2021
 */

#include "questfilltank.h"
#include "physicgameobjectsfile.h"

void FillTank::listener(const CallbackOptions &callback)
{
	Tank* fishTank = (Tank*)callback.getGameObject("tank");
	int waterLevel = fishTank->getWaterLevel();
	if (waterLevel > 400){
		emit Quest::pass();
		callback.deleteGameObject("fillTankinstructions");
	}
}

void FillTank::reset(const CallbackOptions &callback)
{

}

void FillTank::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("fillTankinstructions", "Click the bowl to put the\ndecloronated water into the bowl", QPointF(-5, 0), QPointF(15,3), 100);
	callback.addGameObject(instructionText);
}
