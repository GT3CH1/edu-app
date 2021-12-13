/**
 * Authors - Kenzie Evans, Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */
#include "physicsfilter.h"
// Filter
Filter::Filter(std::string name, QPointF position, double rotation, QPointF scale, QImage img, int layer) :
		PhysicsGameObject(name,position,rotation,scale, createBodyDef(b2_staticBody),img,layer)
{
	oldFilter = false;
}

bool Filter::getOldFilter()
{
	return oldFilter;
}

void Filter::setOldFilter(bool newFilter)
{
	oldFilter = newFilter;
}
