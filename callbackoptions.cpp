#include "callbackoptions.h"
#include <functional>
#include <string>

CallbackOptions::CallbackOptions(std::function<GameObject*(std::string name)> getGameObject, std::function<void(GameObject&)> addGameObject, std::function<void(std::string)> deleteGameObject)
{
	getGameObject = getGameObject;
	addGameObject = addGameObject;
	deleteGameObject = deleteGameObject;
}
