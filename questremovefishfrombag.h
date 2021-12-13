#ifndef FISHTUTORIAL_QUESTREMOVEFISHFROMBAG_H
#define FISHTUTORIAL_QUESTREMOVEFISHFROMBAG_H


#include "quest.h"
#include "physicgameobjectsfile.h"
// Choose Fish not sure if it is necisary or how to determine pass/fail
// just treat a completion as a pass
class RemoveFishFromBag : public Quest
{
	Q_OBJECT
public:
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
	void showText(const CallbackOptions &callback);
signals:
	void fishRemovedFromBag(Fish* f);
};

#endif //FISHTUTORIAL_QUESTREMOVEFISHFROMBAG_H
