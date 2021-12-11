#ifndef SIMPLEDRAGABLE_H
#define SIMPLEDRAGABLE_H

#include "dragable.h"

class SimpleDragable : public Dragable
{
public:
	SimpleDragable(std::string name, QPointF position, double rotation, QPointF scale, int layer);
	virtual void setBody(b2Body* newBody);
private:
	static b2BodyDef constructBodyDef();
};

#endif // SIMPLEDRAGABLE_H
