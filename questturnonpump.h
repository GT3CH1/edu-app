//
// Created by gcpease on 12/11/2021.
//

#ifndef FISHTUTORIAL_QUESTTURNONPUMP_H
#define FISHTUTORIAL_QUESTTURNONPUMP_H
#include "quest.h"
#include "physicgameobjectsfile.h"
//Turn On Water Pump
class TurnOnWaterPump : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
	void showText(const CallbackOptions &callback);
};

#endif //FISHTUTORIAL_QUESTTURNONPUMP_H
