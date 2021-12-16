#ifndef FISHTUTORIAL_QUESTFILLBOWL_H
#define FISHTUTORIAL_QUESTFILLBOWL_H

#include "callbackoptions.h"
#include "quest.h"

class FillBowl : public Quest
{
public:
	void listener(const CallbackOptions &callback) override;
	void showText(const CallbackOptions &callback) override;
};


#endif //FISHTUTORIAL_QUESTFILLBOWL_H
