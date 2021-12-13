/**
 * Authors - Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */

#include "questturnonpump.h"
// TurnOnWaterPump
void TurnOnWaterPump::listener(const CallbackOptions &callback)
{
	WaterPump* waterPump = (WaterPump*)callback.getGameObject("waterpump");
	bool pumpPower = waterPump->getPower();
	if(!pumpPower)
	{
		emit Quest::pass();
	} /*else{
		emit Quest::fail();
	}*/
}

void TurnOnWaterPump::reset(const CallbackOptions &callback)
{

}

void TurnOnWaterPump::showText(const CallbackOptions &callback)
{

}
