/**
 * Authors - Alex Richins, William Erignac
 * Last Modified - 12/14/2021
 *
 * A standard object in the game engine. A GameObject
 * always has at least a transformation (loc,rot,scale)
 * and an image to represent itself.
 */

#include "gameobject.h"

/**
 * @brief Constructs a default monkey GameObject.
 */
GameObject::GameObject() : name("default"), graphic(QImage(":/res/stinkyMonkey.png")), scale(1, 1)
{}

/**
 * @brief Constructs a GameObject with the given parameters.
 * @param name The names of all GameObjects should be unique.
 * @param _rotation The rotation of the object in degrees.
 */
GameObject::GameObject(std::string name, QPointF _position, double _rotation, QPointF _scale, QImage graphic, int layer)
		:
		name(name),
		position(_position.x(), _position.y()),
		rotation(_rotation),
		scale(_scale.x(), _scale.y()),
		graphic(graphic),
		renderLayer(layer)
{}

/**
 * @brief Assign the methods that this object can use
 * to affect / get information from the model.
 * NOTE: To be used by the model.
 */
void GameObject::setCallbacks(CallbackOptions _callbackOptions)
{
	this->callbackOptions = _callbackOptions;
}

/**
 * @brief Returns the location of this GameObject
 * in the active scene.
 * NOTE: The origin of the scene is at (0,0) at the center of
 * the screen. y+ is up and x+ is right.
 */
QPointF GameObject::getLocation()
{
	return QPointF(position.x, position.y);
}

/**
 * @brief Returns the rotation of the object in degrees.
 */
double GameObject::getRotation()
{
	return rotation;
}

/**
 * @brief Returns the scale of the object.
 * NOTE: Scale only affects the size of the image drawn of
 * the GameObject, no other qualities of the GameObject
 * (including physics bodies) are affected by scale.
 */
QPointF GameObject::getScale()
{
	return QPointF(scale.x, scale.y);
}

/**
 * @brief Returns the image used to represent this object.
 */
QImage GameObject::getGraphic()
{
	return graphic;
}

/**
 * @brief Returns the order that this object should be rendered int.
 */
int GameObject::getLayer()
{
	return renderLayer;
}

/**
 * @brief Returns the name of this object.
 */
std::string GameObject::getName() const
{
	return name;
}

/**
 * @brief Returns whether this object should be rendered.
 */
bool GameObject::getToRender()
{
	return render;
}

/**
 * @brief Called every frame by the game engine. Override
 * this to make objects that do things every frame.
 * @param deltaTime The amount of time that has passed since the
 * last update call.
 */
void GameObject::updateObject(float deltaTime)
{}

/**
 * @brief Called once this object is instantiated. Override
 * this to make objects that do things once they're instantiated
 * in the model.
 */
void GameObject::start()
{}

/**
 * @brief Sets the name of the game object.
 * @param name - The name of this game object.
 */
void GameObject::setName(const std::string &name)
{
	GameObject::name = name;
}

/**
 * @brief Sets the graphic of the game object.
 * @param graphic - The graphic/image we want now rendered.
 */
void GameObject::setGraphic(const QImage &graphic)
{
	GameObject::graphic = graphic;
}

/**
 * @brief Sets the new location of this game object in world-coordinates
 * @param location - The location we want this object to be at.
 */
void GameObject::setLocation(QPointF location)
{
	GameObject::position = b2Vec2((float) location.x(), (float) location.y());
}

void GameObject::setRotation(double newRotation)
{
	GameObject::rotation = newRotation;

}

void GameObject::setScale(const b2Vec2 &scale)
{
	GameObject::scale = scale;
}
