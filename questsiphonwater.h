#ifndef FISHTUTORIAL_QUESTSIPHONWATER_H
#define FISHTUTORIAL_QUESTSIPHONWATER_H
#include "quest.h"
#include "physicgameobjectsfile.h"
//Siphon Old Water essentially fill bowl but with a different range
class SiphonOldWater : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
	void showText(const CallbackOptions &callback);
};



#endif //FISHTUTORIAL_QUESTSIPHONWATER_H
