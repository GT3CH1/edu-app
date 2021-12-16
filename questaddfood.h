#ifndef FISHTUTORIAL_QUESTADDFOOD_H
#define FISHTUTORIAL_QUESTADDFOOD_H
#include "quest.h"
#include "physicgameobjectsfile.h"
// Add Food
class AddFood : public Quest
{
public:
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
	void showText(const CallbackOptions &callback);
};

#endif //FISHTUTORIAL_QUESTADDFOOD_H
