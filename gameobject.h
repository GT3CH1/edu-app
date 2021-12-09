#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPoint>
#include <QImage>
#include <string>
#include <Box2D/Box2D.h>

class GameObject
{
protected:
	b2Vec2 position;
	b2Vec2 scale;
	double rotation;

	std::string name;
	QImage graphic;
	int renderLayer;
public:
	GameObject();
	GameObject(std::string name, QPointF, double, QPointF scale, QImage, int);
	QPointF getLocation();
	double getRotation();
	QPointF getScale();
	QImage getGraphic();
	int getLayer();
	std::string getName();
	virtual void updateObject(float);
};

#endif // GAMEOBJECT_H
