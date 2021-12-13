/**
 * Authors - Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */

#include "questturnoffpump.h"
// TurnOffWaterPump
void TurnOffWaterPump::listener(const CallbackOptions &callback)
{
	WaterPump* waterFilter = (WaterPump*)callback.getGameObject("waterpump");
	bool pumpPower = waterFilter->getPower();
	if(pumpPower)
	{
		emit pass();
	} /*else{
		emit Quest::fail();
	}*/
}

void TurnOffWaterPump::reset(const CallbackOptions &callback)
{

}

void TurnOffWaterPump::showText(const CallbackOptions &callback)
{

}
