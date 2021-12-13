#include "physicsgameobject.h"
class Spigot : public PhysicsGameObject
{
public:
	Spigot();
	Spigot(std::string name, QPointF position, double rotation, QPointF scale, b2BodyDef body, QImage image);
	bool getPower();
	void setPower(bool newPower);
	virtual void setBody(b2Body* newBody);
	void onMouseHold(QPointF position);
private:
	bool power;
};