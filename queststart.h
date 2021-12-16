#ifndef START_H
#define START_H

#include "quest.h"

class Start : public Quest
{
public:
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
	void showText(const CallbackOptions &callback);
};

#endif // START_H
