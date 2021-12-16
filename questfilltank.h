#ifndef FISHTUTORIAL_QUESTFILLTANK_H
#define FISHTUTORIAL_QUESTFILLTANK_H

#include "callbackoptions.h"
#include "quest.h"

class FillTank : public Quest
{
public:
	void listener(const CallbackOptions &callback) override;
	void showText(const CallbackOptions &callback) override;
};

#endif //FISHTUTORIAL_QUESTFILLTANK_H
