#ifndef FISHTUTORIAL_QUESTADDFISH_H
#define FISHTUTORIAL_QUESTADDFISH_H


#include "quest.h"
#include "physicgameobjectsfile.h"

// Add Fish
class AddFish : public Quest
{
public:
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
	void showText(const CallbackOptions &callback);
};

#endif //FISHTUTORIAL_QUESTADDFISH_H
