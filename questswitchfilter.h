#ifndef FISHTUTORIAL_QUESTSWITCHFILTER_H
#define FISHTUTORIAL_QUESTSWITCHFILTER_H

#include "quest.h"
#include "physicgameobjectsfile.h"
// swap Filter
class SwitchFilter : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
	void showText(const CallbackOptions &callback);
};

#endif //FISHTUTORIAL_QUESTSWITCHFILTER_H
