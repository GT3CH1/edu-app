/**
 * Authors - Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */

#include "questsiphonwater.h"
// SiphonOldWater
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

}
