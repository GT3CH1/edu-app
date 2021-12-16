#ifndef FISHTUTORIAL_QUESTCHOOSEFISH_H
#define FISHTUTORIAL_QUESTCHOOSEFISH_H

#include "quest.h"
#include "physicgameobjectsfile.h"
// Choose Fish not sure if it is necisary or how to determine pass/fail
class ChooseFish : public Quest
{
public:
	void listener(const CallbackOptions &callback) override;
	void showText(const CallbackOptions &callback) override;
};

#endif //FISHTUTORIAL_QUESTCHOOSEFISH_H
