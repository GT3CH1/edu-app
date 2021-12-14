#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include "physicsgameobject.h"

class StartButton : public PhysicsGameObject
{
public:
	StartButton();
	virtual void setBody(b2Body* newBody);
	void onMouseClick(QPointF position);
	bool getClicked();
private:
	bool clicked;
};

#endif // STARTBUTTON_H
