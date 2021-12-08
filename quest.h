#ifndef QUEST_H
#define QUEST_H

#include <QObject>
#include "physicsgameobject.h"
#include "callbackoptions.h"

/**
 * @brief Abstract class that has a listener and reset so that each Quest can communicate with the model.
 */

class Quest : public QObject
{
	Q_OBJECT
public:
	virtual void listener(const CallbackOptions &callback) = 0;
	virtual void reset(const CallbackOptions &callback) = 0;

signals:
	void pass();
	void fail();
};

#endif // QUEST_H
