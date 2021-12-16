/**
 * Authors - Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */

#include "questsiphonwater.h"

void SiphonOldWater::listener(const CallbackOptions &callback)
{
	Bowl* bowl = (Bowl*)callback.getGameObject("bowl");
	int waterLevel = bowl->getWaterLevel();
	/*if (waterLevel > 200){
		emit Quest::fail();
	}else*/ if (waterLevel > 100){
		emit Quest::pass();
	}
}

void SiphonOldWater::reset(const CallbackOptions &callback)
{

}

void SiphonOldWater::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("siphonWaterinstructions", "SIPHON BABY", QPointF(4, 1), QPointF(15,3), 100);
	callback.addGameObject(instructionText);
}
