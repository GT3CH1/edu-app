#ifndef FISHTUTORIAL_QUESTFILLBOWL_H
#define FISHTUTORIAL_QUESTFILLBOWL_H
#include "callbackoptions.h"
#include "quest.h"

// Fill Bowl
class FillBowl : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
	void showText(const CallbackOptions &callback);
};


#endif //FISHTUTORIAL_QUESTFILLBOWL_H
