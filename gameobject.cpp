#include "gameobject.h"

GameObject::GameObject() : location(QPoint(0, 0)), rotation(75), graphic(QImage(QString(":/stinkyMonkey.png"))) {}
GameObject::GameObject(QPoint location, double rotation, QImage graphic) : location(location), rotation(rotation), graphic(graphic) {}

QPoint GameObject::getLocation(){
	return location;
}
double GameObject::getRotation(){
	return rotation;
}
QImage GameObject::getGraphic(){
	return graphic;
}

void GameObject::updateObject(float deltaTime){
	rotation += deltaTime*10;
}
