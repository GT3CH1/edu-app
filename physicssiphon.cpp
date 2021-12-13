/**
 * Authors - Kenzie Evans, Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */
#include "physicssiphon.h"
// Siphon
Siphon::Siphon() :
		PhysicsGameObject("siphon", QPointF(7,-3.75), 0, QPointF(2,2), createBodyDef(b2_staticBody), QImage(":/res/siphon.png")) { }
