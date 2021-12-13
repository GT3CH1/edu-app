/**
 * Authors - Kenzie Evans, Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */

#include "physicswaterpump.h"
// WaterPump
WaterPump::WaterPump(std::string name, QPointF position, double rotation, QPointF scale, QImage img, int layer) :
		PhysicsGameObject(name,position,rotation,scale, createBodyDef(b2_staticBody),img,layer)
{
	power = false;
}

bool WaterPump::getPower()
{
	return power;
}

void WaterPump::setPower(bool newPower)
{
	power = newPower;
}
