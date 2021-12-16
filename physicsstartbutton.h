#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include "physicsgameobject.h"

class StartButton : public PhysicsGameObject
{
public:
	StartButton();
	void setBody(b2Body* newBody) override;
	void onMouseClick(QPointF position) override;
	bool getClicked() const;
private:
	bool clicked;
};

#endif // STARTBUTTON_H
