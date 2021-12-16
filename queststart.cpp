/**
 * Authors -  Kenzie Evans, Alex Richins
 * Last Modified - 12/15/2021
 */
#include "queststart.h"
#include "physicgameobjectsfile.h"

void Start::listener(const CallbackOptions &callback)
{
	auto startButton = (StartButton*)callback.getGameObject("startbutton");
	if (startButton->getClicked()){
		emit pass();
		callback.deleteGameObject("waitinstructions");
		callback.deleteGameObject("waitinstructions2");
	}
}

void Start::reset(const CallbackOptions &callback)
{

}

void Start::showText(const CallbackOptions &callback)
{
	GameObject* instructionText = createTextImage("startinstructions", "FISH TUTORIAL\n", QPointF(0, 2), QPointF(25,5), 100);
	callback.addGameObject(instructionText);
	GameObject* instructionText2 = createTextImage("waitinstructions2", "click start to learn the basics of caring\nfor your fish for the first few days", QPointF(0, 0), QPointF(15,3), 100);
	callback.addGameObject(instructionText2);
}
