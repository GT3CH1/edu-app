#ifndef CALLBACKOPTIONS_H
#define CALLBACKOPTIONS_H
#include <functional>
#include <string>
#include "gameobject.h"

struct CallbackOptions
{
public:
	CallbackOptions(std::function<GameObject*(std::string)>, std::function<void(GameObject&)>, std::function<void(std::string)>);

	/**
	 * @brief getGameObject
	 */
	std::function<GameObject*(std::string)> getGameObject;

	std::function<void(GameObject&)> addGameObject;

	std::function<void(std::string)> deleteGameObject;
};

#endif // CALLBACKOPTIONS_H
