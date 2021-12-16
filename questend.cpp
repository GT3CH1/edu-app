/**
 * Authors -  Kenzie Evans, Alex Richins
 * Last Modified - 12/15/2021
 */
#include "questend.h"
#include "physicgameobjectsfile.h"

void End::listener(const CallbackOptions &callback)
{
	auto startButton = (StartButton*)callback.getGameObject("startbutton");
	if (startButton->getClicked()){
		emit pass();
		callback.deleteGameObject("waitinstructions");
		callback.deleteGameObject("waitinstructions2");
	}
}

void End::reset(const CallbackOptions &callback)
{

}

void End::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("startinstructions", "CONGRATS", QPointF(0, 2), QPointF(25,5), 100);
	callback.addGameObject(instructionText);
	GameObject* instructionText2 = createTextImage("waitinstructions2", "you can now take care of your fish for the first few days!\nclick the button below to review", QPointF(0, 0), QPointF(15,3), 100);
	callback.addGameObject(instructionText2);
}
