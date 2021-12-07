#ifndef QUEST_H
#define QUEST_H

#include <QObject>
#include "callbackoptions.h"

class Quest
{
public:
	virtual void listener(const CallbackOptions &callback) = 0;
	virtual void reset(const CallbackOptions &callback) = 0;

signals:
	void pass();
	void fail();
};

#endif // QUEST_H
