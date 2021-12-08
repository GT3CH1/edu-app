#include "questsfile.h"

// FillBowl
void FillBowl::listener(const CallbackOptions &callback)
{
	Bowl* bowl = (Bowl*)callback.getGameObject("bowl");
	int waterLevel = bowl->getWaterLevel();
	/*if (waterLevel > 300){
		emit Quest::fail();
	}else */ if (waterLevel > 200){
		emit Quest::pass();
	}
}

void FillBowl::reset(const CallbackOptions &callback)
{

}

// FillTank
void FillTank::listener(const CallbackOptions &callback)
{
	Tank* fishTank = (Tank*)callback.getGameObject("fishtank");
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

// ChooseFish
void ChooseFish::listener(const CallbackOptions &callback)
{

}

void ChooseFish::reset(const CallbackOptions &callback)
{

}

// AddFish
void AddFish::listener(const CallbackOptions &callback)
{
	Fish* fishie = (Fish*)callback.getGameObject("fish");
	bool fishInTank = fishie->getInTank();
	if(fishInTank){
		emit Quest::pass();
	} /*else{
		emit Quest::fail();
	}*/
}
void AddFish::reset(const CallbackOptions &callback)
{

}

// Age Water
void Wait::listener(const CallbackOptions &callback)
{
	Clock* clock = (Clock*)callback.getGameObject("Clock");
	int time = clock->getTime();
	if (time > 24){
		emit Quest::pass();
	}
}

void Wait::reset(const CallbackOptions &callback)
{

}

// AddFood
void AddFood::listener(const CallbackOptions &callback)
{
	FoodContainer* fishFlakes = (FoodContainer*)callback.getGameObject("foodcontainer");
	int foodGiven = fishFlakes->getShaken();
	if (foodGiven > 20){ // TODO: work with william to determine how the food container will behave and figure what determines enough food
		emit Quest::pass();
	}
}

void AddFood::reset(const CallbackOptions &callback)
{

}

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

// SwitchFilter
void SwitchFilter::listener(const CallbackOptions &callback)
{
	Filter* waterFilter = (Filter*)callback.getGameObject("waterfilter");
	bool filterOld = waterFilter->getOldFilter();
	if(!filterOld){
		emit Quest::pass();
	} /*else{
		emit Quest::fail();
	}*/
}

void SwitchFilter::reset(const CallbackOptions &callback)
{

}

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
