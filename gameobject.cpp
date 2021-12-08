/**
 * Authors - Alex Richins, William Erignac
 * Last Modified - 12/3/2021
 *
 * A standard object in the game engine. A GameObject
 * always has at least a transformation (loc,rot,scale)
 * and an image to represent itself.
 */

#include "gameobject.h"

/**
 * @brief Constructs a default monkey GameObject.
 */
GameObject::GameObject() : name("default"), graphic(QImage(":/res/stinkyMonkey.png")), scale(1,1) {}

/**
 * @brief Constructs a GameObject with the given parameters.
 * @param name The names of all GameObjects should be unique.
 * @param _rotation The rotation of the object in degrees.
 */
GameObject::GameObject(std::string name, QPointF _position, double _rotation, QPointF _scale, QImage graphic) :
	name(name),
	position(_position.x(), _position.y()),
	rotation(_rotation),
	scale(_scale.x(), _scale.y()),
	graphic(graphic)
{ }

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
QImage GameObject::getGraphic(){
	return graphic;
}

/**
 * @brief Returns the name of this object.
 */
std::string GameObject::getName()
{
	return name;
}

/**
 * @brief Called every frame by the game engine. Override
 * this to make objects that do things every frame.
 * @param deltaTime The amount of time that has passed since the
 * last update call.
 */
void GameObject::updateObject(float deltaTime){ }
