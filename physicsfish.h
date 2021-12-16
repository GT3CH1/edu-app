#ifndef FISH_H
#define FISH_H

#include "physicsgameobject.h"
#include "draggable.h"

class Fish : public Draggable
{
public:
	enum FISH_TYPE {PLECO, GOLDFISH, SIMPLE};
	Fish(std::string name = "Jim Carey",
		 QPointF position = QPointF(4.5, -2),
		 double rotation = 0,
		 QPointF scale = QPointF(2, 2),
		 QImage image = QImage(":/res/simple_fish.png"),
		 FISH_TYPE fishType = SIMPLE);
	void setInTank(bool state);
	void setFishType(FISH_TYPE fishType);
	void setBody(b2Body* newBody) override;
	void onMouseClick(QPointF position) override;
	void setSelected(bool state);
	bool isSelected() const;
	bool isInTank() const;
private:
	bool inTank = false;
	bool selected = false;
	bool inBag = true;
	FISH_TYPE type = GOLDFISH;
	void putFishInBag();
};

#endif // FISH_H
