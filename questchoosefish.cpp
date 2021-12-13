/**
 * Authors - Alex Richins, Kenzie Evans, Gavin Pease
 * Last Modified - 12/12/2021
 */

#include "questchoosefish.h"
#include <QDebug>
#include <QPainter>

ChooseFish::ChooseFish(){
	callShowText = true;
}

void ChooseFish::listener(const CallbackOptions &callback)
{
	auto pleco = (Fish *) callback.getGameObject("pleco");
	auto goldfish = (Fish *) callback.getGameObject("goldfish");
	auto moorish = (Fish *) callback.getGameObject("moorish");
	bool fishSelected = (pleco->isSelected() || goldfish->isSelected() || moorish->isSelected());
	if (fishSelected)
	{		
		callback.deleteGameObject("ChooseFishinstructions");
		if (pleco->isSelected())
		{
			goldfish->setClickable(false);
			moorish->setClickable(false);
		}
		if (goldfish->isSelected())
		{
			pleco->setClickable(false);
			moorish->setClickable(false);
		}
		if (moorish->isSelected())
		{
			goldfish->setClickable(false);
			pleco->setClickable(false);
		}
		emit Quest::pass();
	}
}

void ChooseFish::reset(const CallbackOptions &callback)
{

}

void ChooseFish::showText(const CallbackOptions &callback)
{
		GameObject* instructionText = createTextImage("ChooseFishinstructions", "Please click and drag one of the\nfish below to put it into the tank", QPointF(-5, -2), QPointF(12,3), 100);
		callback.addGameObject(instructionText);
}
