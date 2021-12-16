#ifndef FISHTUTORIAL_QUESTADDFISH_H
#define FISHTUTORIAL_QUESTADDFISH_H

#include "quest.h"
#include "physicgameobjectsfile.h"

// Add Fish
class AddFish : public Quest
{
public:
	void listener(const CallbackOptions &callback) override;
	void showText(const CallbackOptions &callback) override;
};

#endif //FISHTUTORIAL_QUESTADDFISH_H
