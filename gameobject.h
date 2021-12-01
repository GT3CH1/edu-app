#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPoint>
#include <QImage>
#include <string>

class GameObject
{
protected:
	QTransform offset;
	std::string name;
	QImage graphic;
public:
	GameObject();
	GameObject(std::string name, QPoint, double, QImage);
	GameObject(std::string, QTransform, QImage);
	QPoint getLocation();
	double getRotation();
	QImage getGraphic();
	QTransform getOffset();
	virtual void updateObject(float);
};

#endif // GAMEOBJECT_H
