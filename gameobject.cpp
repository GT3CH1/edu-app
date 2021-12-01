#include "gameobject.h"

GameObject::GameObject() : name("default"), offset(QTransform()), graphic(QImage(QString(":/stinkyMonkey.png"))) {}
GameObject::GameObject(std::string name, QPoint location, double rotation, QImage graphic) : name(name)
{
	QTransform blank;
	blank.translate(location.x(), location.y());
	blank.rotate(rotation);
	offset = blank;
}
GameObject::GameObject(std::string name, QTransform offset, QImage graphic) : name(name), offset(offset), graphic(graphic) {}

QImage GameObject::getGraphic(){
	return graphic;
}

void GameObject::updateObject(float deltaTime){
	offset.rotate(deltaTime*10);
}
