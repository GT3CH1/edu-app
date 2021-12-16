#ifndef CALLBACKOPTIONS_H
#define CALLBACKOPTIONS_H

#include <functional>
#include <string>
#include <Box2D/Box2D.h>

struct CallbackOptions
{
public:

	/**
	 * @brief getGameObject is a function that allows to get a game object
	 */
	std::function<void*(std::string)> getGameObject;

	/**
	 * @brief addGameObject is a function that adds a game object
	 */
	std::function<void(void*)> addGameObject;

	/**
	 * @brief deleteGameObject is a function that removes game object
	 */
	std::function<void(std::string)> deleteGameObject;

	/**
	 * @brief addJoint is a function to add a joint
	 */
	std::function<b2Joint*(b2JointDef*)> addJoint;

	/**
	 * @brief destroyJoint is a function to destroy a joint
	 */
	std::function<void(b2Joint* toDestory)> destroyJoint;

	/**
	 * @brief getDeltaTime is a funtion that will give the give
	 */
	std::function<float()> getDeltaTime;

	CallbackOptions(std::function<void*(std::string)>, std::function<void(void*)>, std::function<void(std::string)>, std::function<b2Joint*(b2JointDef*)>, std::function<void(b2Joint* toDestory)>, std::function<float()> getDeltaTime);

	CallbackOptions();
};

#endif // CALLBACKOPTIONS_H
