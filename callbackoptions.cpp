#include "callbackoptions.h"
#include <functional>
#include <string>

CallbackOptions::CallbackOptions(std::function<void*(std::string name)> getGameObject, std::function<void(void*)> addGameObject, std::function<void(std::string)> deleteGameObject)
{
	this->getGameObject = getGameObject;
	this->addGameObject = addGameObject;
	this->deleteGameObject = deleteGameObject;
}

CallbackOptions::CallbackOptions()
{
}
