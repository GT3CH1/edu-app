#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPoint>
#include <QImage>

class GameObject
{
protected:
	// TODO: Look into just storing a QTransform to store the offset (location) and rotation of QImage
	QPoint location;
	double rotation;
	QImage graphic;
public:
	GameObject();
	GameObject(QPoint, double, QImage);
	QPoint getLocation();
	double getRotation();
	QImage getGraphic();
	virtual void updateObject(float);
};

#endif // GAMEOBJECT_H
