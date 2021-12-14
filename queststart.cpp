#include "queststart.h"
#include "physicgameobjectsfile.h"

void Start::listener(const CallbackOptions &callback)
{
	auto startButton = (StartButton*)callback.getGameObject("startbutton");
	if (startButton->getClicked())
		emit pass();
}

void Start::reset(const CallbackOptions &callback)
{

}

void Start::showText(const CallbackOptions &callback)
{

}
