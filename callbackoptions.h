#ifndef CALLBACKOPTIONS_H
#define CALLBACKOPTIONS_H

#include <functional>
#include <string>

/**
 * @brief The CallbackOptions struct is the means through which GameObjects can affect the model.
 */

struct CallbackOptions
{
public:
	std::function<void*(std::string)> getGameObject;

	std::function<void(void*)> addGameObject;

	std::function<void(std::string)> deleteGameObject;

	CallbackOptions(std::function<void*(std::string)>, std::function<void(void*)>, std::function<void(std::string)>);

	CallbackOptions();
};

#endif // CALLBACKOPTIONS_H
