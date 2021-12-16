/**
 * Authors - Alex Richins, Gavin Pease, Kenzie Evans, William Erignac
 * Last Modified - 12/12/2021
 *
 * An object that stores water to be
 * put into the fish tank.
 */

#include "physicsbowl.h"
#include "physicstank.h"
#include <QPainter>

/**
 * @brief Constructs a bowl game object
 */
Bowl::Bowl(QPointF position) :
	PhysicsGameObject("bowl", position, 0, QPointF(7, 3.5), PhysicsGameObject::createBodyDef(b2_staticBody), QImage(":/res/bowl.png"))
{
	waterLevel = 0;
	emptyBucket = graphic;
	clickable = false;
}

/**
 * @brief Returns the water level
 * @return the current water level
 */
int Bowl::getWaterLevel() const
{
	return waterLevel;
}

/**
 * @brief Sets the new water level
 * @param newWaterLevel - the water level to set the bowl at
 */
void Bowl::setWaterLevel(int newWaterLevel)
{
	waterLevel = newWaterLevel;
	drawWater();
}

/**
 * @brief Increments the water level up by 1
 */
void Bowl::raiseWaterLevel()
{
	waterLevel++;
	drawWater();
}

/**
 * @brief Sets the body of the game object
 * @param newBody - the body to set the game object to
 */
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

/**
 * @brief When the bowl is full, moves the water to the tank when clicked on
 * @param position - the position where the mouse is clicked
 */
void Bowl::onMouseClick(QPointF position)
{
	//When the bowl is clicked, it should be emptied into the tank.
	setWaterLevel(0);
	Tank* tank = (Tank*)callbackOptions.getGameObject("tank");
	tank->setWaterLevel(500);
}

/**
 * @brief Draws the water in the bowl
 */
void Bowl::drawWater()
{
	//Calculate where the top of the water should be.
	float waterLevelHeight = emptyBucket.height() - waterLevel*emptyBucket.height()/100;
	//Start with a transparent image...
	QImage water(emptyBucket.width(), emptyBucket.height(), QImage::Format::Format_RGBA64);
	water.fill(Qt::transparent);
	QPainter painter(&water);
	//Set the brush to a water-ish color.
	painter.setBrush(QColor(0, 75, 225, 225));
	//Draw a full amount of water.
	painter.drawEllipse(0 + emptyBucket.width()*0.075, -emptyBucket.height(), emptyBucket.width()*0.85, emptyBucket.height()*1.95);
	//Remove some of the water to get the desired height.
	QBrush transparentBrush;
	transparentBrush.setStyle(Qt::BrushStyle::SolidPattern);
	transparentBrush.setColor(Qt::transparent);
	//Draw the bowl itself.
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.fillRect(0, 0, emptyBucket.width(), waterLevelHeight, transparentBrush);
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawImage(QPointF(0, 0), emptyBucket);
	painter.end();
	graphic = water;
}
