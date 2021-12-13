#ifndef FISHTUTORIAL_QUESTTURNOFFPUMP_H
#define FISHTUTORIAL_QUESTTURNOFFPUMP_H
#include "quest.h"
#include "physicgameobjectsfile.h"
//Turn Off Water Pump
class TurnOffWaterPump : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
	void showText(const CallbackOptions &callback);
};

#endif //FISHTUTORIAL_QUESTTURNOFFPUMP_H
