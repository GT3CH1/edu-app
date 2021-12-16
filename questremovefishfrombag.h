#ifndef FISHTUTORIAL_QUESTREMOVEFISHFROMBAG_H
#define FISHTUTORIAL_QUESTREMOVEFISHFROMBAG_H

#include "quest.h"
#include "physicgameobjectsfile.h"

class RemoveFishFromBag : public Quest
{
	Q_OBJECT
public:
	void listener(const CallbackOptions &callback) override;
	void showText(const CallbackOptions &callback) override;
signals:
	void fishRemovedFromBag(AnimatedFish* f);
};

#endif //FISHTUTORIAL_QUESTREMOVEFISHFROMBAG_H
