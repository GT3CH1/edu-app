#ifndef END_H
#define END_H

#include "quest.h"

class End : public Quest
{
public:
	void listener(const CallbackOptions &callback);
	void reset(const CallbackOptions &callback);
	void showText(const CallbackOptions &callback);
};

#endif // END_H
