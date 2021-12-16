#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPoint>
#include <QImage>
#include <string>
#include <Box2D/Box2D.h>
#include <callbackoptions.h>

class GameObject
{
protected:
	b2Vec2 position;
public:
	void setScale(const b2Vec2 &scale);
protected:
	b2Vec2 scale;
	double rotation;
	std::string name;
	QImage graphic;
	int renderLayer;
	bool render = true;
	CallbackOptions callbackOptions;
public:
	GameObject();
	GameObject(std::string name, QPointF, double, QPointF scale, QImage, int);
	void setCallbacks(CallbackOptions callbackOptions);
	QPointF getLocation() const;
	double getRotation() const;
	QPointF getScale() const;
	QImage getGraphic();
	bool getToRender() const;
	void setName(const std::string &name);
	void setGraphic(const QImage &graphic);
	void setLocation(QPointF location);
	virtual void setRotation(double newRotation);
	int getLayer() const;
	std::string getName() const;
	virtual void start();
	virtual void updateObject(float);
};

#endif // GAMEOBJECT_H
