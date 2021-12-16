#ifndef FISHTUTORIAL_QUESTWAIT_H
#define FISHTUTORIAL_QUESTWAIT_H

#include "quest.h"
#include "physicgameobjectsfile.h"
// Age Water
class Wait : public Quest
{
public:
	void listener(const CallbackOptions &callback) override;
	void showText(const CallbackOptions &callback) override;
};

#endif //FISHTUTORIAL_QUESTWAIT_H
