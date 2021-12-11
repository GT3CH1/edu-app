#ifndef CALLBACKOPTIONS_H
#define CALLBACKOPTIONS_H

#include <functional>
#include <string>
#include <Box2D/Box2D.h>
/**
 * @brief The CallbackOptions struct is the means through which GameObjects can affect the model.
 */
struct CallbackOptions
{
public:
	std::function<void*(std::string)> getGameObject;

	std::function<void(void*)> addGameObject;

	std::function<void(std::string)> deleteGameObject;

	std::function<b2Joint*(b2JointDef*)> addJoint;

	std::function<void(b2Joint* toDestory)> destroyJoint;

	CallbackOptions(std::function<void*(std::string)>, std::function<void(void*)>, std::function<void(std::string)>, std::function<b2Joint*(b2JointDef*)>, std::function<void(b2Joint* toDestory)>);

	CallbackOptions();
};

#endif // CALLBACKOPTIONS_H
