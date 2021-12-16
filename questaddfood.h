#ifndef FISHTUTORIAL_QUESTADDFOOD_H
#define FISHTUTORIAL_QUESTADDFOOD_H

#include "quest.h"
#include "physicgameobjectsfile.h"

class AddFood : public Quest
{
public:
	void listener(const CallbackOptions &callback) override;
	void showText(const CallbackOptions &callback) override;
};

#endif //FISHTUTORIAL_QUESTADDFOOD_H
