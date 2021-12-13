//
// Created by gcpease on 12/11/2021.
//

#ifndef FISHTUTORIAL_QUESTWAIT_H
#define FISHTUTORIAL_QUESTWAIT_H


#include "quest.h"
#include "physicgameobjectsfile.h"
// Age Water
class Wait : public Quest
{
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
	void showText(const CallbackOptions &callback);
};



#endif //FISHTUTORIAL_QUESTWAIT_H
