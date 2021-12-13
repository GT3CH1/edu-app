#include "physicsgameobject.h"
#include "dragable.h"
class Fish : public Dragable {
public:
	enum FISH_TYPE {PLECO,GOLDFISH,SIMPLE};
	Fish(std::string name = "Jim Carey",
	     QPointF position = QPointF(4.5, -2),
	     double rotation = 0,
	     QPointF scale = QPointF(2, 2),
	     QImage image = QImage(":/res/simple_fish.png"),
		 FISH_TYPE fishType = SIMPLE);
	bool isInTank();
	void setInTank(bool state);
	void setFishType(FISH_TYPE fishType);
	void setBody(b2Body* newBody) override;
	void onMouseClick(QPointF position);
	bool isSelected() const;
	void setSelected(bool state);
public:
	bool isInBag() const;
	void setInBag(bool inBag);
private:
	bool inTank = false;
	bool selected = false;
	bool inBag = true;
	FISH_TYPE type;
	void putFishInBag();
	void removeFishFromBag();
};
