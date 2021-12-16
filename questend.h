#ifndef END_H
#define END_H

#include "quest.h"

class End : public Quest
{
public:
	void listener(const CallbackOptions &callback) override;
	void showText(const CallbackOptions &callback) override;
};

#endif // END_H
