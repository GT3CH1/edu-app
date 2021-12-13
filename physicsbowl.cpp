/**
 * Authors - Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */
#include "physicsbowl.h"
#include "physicstank.h"
#include <QPainter>
// Bowl
Bowl::Bowl() :
		PhysicsGameObject("bowl", QPointF(-8,-4), 0, QPointF(3,1.5), PhysicsGameObject::createBodyDef(b2_dynamicBody), QImage(":/res/bucket.png"))
{
	waterLevel = 0;
	emptyBucket = graphic;
	clickable = false;
}

int Bowl::getWaterLevel()
{
	return waterLevel;
}

void Bowl::setWaterLevel(int newWaterLevel)
{
	waterLevel = newWaterLevel;
	drawWater();
}

void Bowl::raiseWaterLevel()
{
	waterLevel++;
	drawWater();
}

void Bowl::setBody(b2Body *newBody)
{
	b2PolygonShape wall;
	wall.SetAsBox(1,0.75,b2Vec2(0,0),0);

	b2FixtureDef wallFixture;
	wallFixture.shape = &wall;
	wallFixture.isSensor = false;

	newBody->CreateFixture(&wallFixture);
	PhysicsGameObject::setBody(newBody);
}

void Bowl::onMouseClick(QPointF position)
{
	setWaterLevel(0);
	Tank* tank = (Tank*)callbackOptions.getGameObject("tank");
	tank->setWaterLevel(500);
}

void Bowl::drawWater()
{
	QImage water(emptyBucket.width(), emptyBucket.height(), QImage::Format::Format_RGBA64);
	water.fill(Qt::transparent);
	QPainter painter(&water);
	painter.setBrush(QColor(0,75,225,225));
	painter.drawRect(0, emptyBucket.height() - waterLevel*emptyBucket.height()/100, emptyBucket.width()-2, waterLevel*emptyBucket.height()/100);
	painter.drawImage(QPointF(0,0), emptyBucket);
	painter.end();
	graphic = water;
}
