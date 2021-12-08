#ifndef QUESTSFILE_H
#define QUESTSFILE_H

#include "quest.h"
#include "physicgameobjectsfile.h"

// Fill Bowl
class FillBowl : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
};

class FillTank : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
};

// Choose Fish not sure if it is necisary or how to determine pass/fail
class ChooseFish : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
};

// Add Fish
class AddFish : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
};

// Age Water
class Wait : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
};

// Add Food

class AddFood : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
};

//Turn Off Water Pump
class TurnOffWaterPump : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
};

//Turn On Water Pump
class TurnOnWaterPump : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
};

// swap Filter
class SwitchFilter : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
};

//Siphon Old Water essentially fill bowl but with a different range
class SiphonOldWater : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
};


#endif // QUESTSFILE_H
