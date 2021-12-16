#ifndef FISHTUTORIAL_QUESTFILLTANK_H
#define FISHTUTORIAL_QUESTFILLTANK_H
#include "callbackoptions.h"
#include "quest.h"
class FillTank : public Quest
{
public:
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
	void showText(const CallbackOptions &callback);
};

#endif //FISHTUTORIAL_QUESTFILLTANK_H
