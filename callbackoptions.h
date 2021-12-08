#ifndef CALLBACKOPTIONS_H
#define CALLBACKOPTIONS_H

#include <functional>
#include <string>
#include "physicsgameobject.h"

/**
 * @brief The CallbackOptions struct is the means through which GameObjects can affect the model.
 */

struct CallbackOptions
{
public:
	CallbackOptions(std::function<GameObject*(std::string)>, std::function<void(GameObject&)>, std::function<void(std::string)>);

	std::function<GameObject*(std::string)> getGameObject;

	std::function<void(GameObject&)> addGameObject;

	std::function<void(std::string)> deleteGameObject;
};

#endif // CALLBACKOPTIONS_H
