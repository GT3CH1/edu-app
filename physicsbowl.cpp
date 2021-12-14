/**
 * Authors - Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */
#include "physicsbowl.h"
#include "physicstank.h"
#include <QPainter>
// Bowl
Bowl::Bowl(QPointF position) :
		PhysicsGameObject("bowl", position, 0, QPointF(7,3.5), PhysicsGameObject::createBodyDef(b2_staticBody), QImage(":/res/bowl.png"))
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
	wall.SetAsBox(scale.x/2, scale.y/2);

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
	float waterLevelHeight = emptyBucket.height() - waterLevel*emptyBucket.height()/100;

	QImage water(emptyBucket.width(), emptyBucket.height(), QImage::Format::Format_RGBA64);
	water.fill(Qt::transparent);
	QPainter painter(&water);
	painter.setBrush(QColor(0,75,225,225));
	painter.drawEllipse(0 + emptyBucket.width()*0.075,-emptyBucket.height(),emptyBucket.width()*0.85,emptyBucket.height()*2);
	QBrush transparentBrush;
	transparentBrush.setStyle(Qt::BrushStyle::SolidPattern);
	transparentBrush.setColor(Qt::transparent);
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.fillRect(0,0,emptyBucket.width(), waterLevelHeight,transparentBrush);
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawImage(QPointF(0,0), emptyBucket);
	painter.end();
	graphic = water;
}
