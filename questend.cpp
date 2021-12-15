#include "questend.h"
#include "physicgameobjectsfile.h"

void End::listener(const CallbackOptions &callback)
{
	auto startButton = (StartButton*)callback.getGameObject("startbutton");
	if (startButton->getClicked())
		emit pass();
}

void End::reset(const CallbackOptions &callback)
{

}

void End::showText(const CallbackOptions &callback)
{

}
