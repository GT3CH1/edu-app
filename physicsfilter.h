#include "physicsgameobject.h"
class Filter : public PhysicsGameObject
{
public:
	Filter(std::string name = "filter",
		   QPointF position = QPointF(0.75,0.25),
		   double rotation = 0,
		   QPointF scale = QPointF(1,1),
		   QImage image = QImage(":/res/filter.png"),
		   int layer= 10);
	bool getOldFilter();
	void setOldFilter(bool newFilter);

private:
	bool oldFilter;
};
