#ifndef START_H
#define START_H

#include "quest.h"

class Start : public Quest
{
public:
	void listener(const CallbackOptions &callback) override;
	void showText(const CallbackOptions &callback) override;
};

#endif // START_H
