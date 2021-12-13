/**
 * Authors - Alex Richins
 * Last Modified - 12/12/2021
 */
#include "callbackoptions.h"
#include <functional>
#include <string>

CallbackOptions::CallbackOptions(std::function<void*(std::string name)> getGameObject, std::function<void(void*)> addGameObject, std::function<void(std::string)> deleteGameObject,
								 std::function<b2Joint*(b2JointDef*)> _addJoint, std::function<void(b2Joint* toDestory)> _destroyJoint, std::function<float()> _getDeltaTime)
{
	this->getGameObject = getGameObject;
	this->addGameObject = addGameObject;
	this->deleteGameObject = deleteGameObject;
	this->addJoint = _addJoint;
	this->destroyJoint = _destroyJoint;
	this->getDeltaTime = _getDeltaTime;
}

CallbackOptions::CallbackOptions()
{
}
