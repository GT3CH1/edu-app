#include "physicsgameobject.h"
class WaterPump : public PhysicsGameObject
{
public:
	WaterPump(std::string name = "pump",
	          QPointF position = QPointF(0.75,-0.25),
	          double rotation = 0,
	          QPointF scale = QPointF(1.25,1.25),
	          QImage image = QImage(":/res/pump.png"),
	          int layer= 10);
	bool getPower();
	void setPower(bool newPower);

private:
	bool power;
};