/**
 * Authors - Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */
#ifndef QUEST_H
#define QUEST_H

#include <QObject>
#include "physicsgameobject.h"
#include "callbackoptions.h"
#include "scenestate.h"
#include <QPainter>

/**
 * @brief Abstract class that has a listener and reset so that each Quest can communicate with the model.
 */

class Quest : public QObject
{
	Q_OBJECT
	// A pointer to the game object, so we can control whether or not we can click on it.
	SCENE_STATE questSceneState;
public:
	Quest() : questSceneState(SCENE_STATE::PREPARE_TANK) {}
	explicit Quest(SCENE_STATE scene) : questSceneState(scene){}

	virtual void listener(const CallbackOptions &callback) = 0;
	virtual void reset(const CallbackOptions &callback) = 0;
	virtual void showText(const CallbackOptions &callback) = 0;
protected:
	static GameObject* createTextImage(std::string name, QString text, QPointF placement, QPointF scale, int layer) {
		QImage textImage(scale.x()/3*100, scale.y()/3*100, QImage::Format::Format_RGBA64);
		textImage.fill(Qt::transparent);
		QPainter textPainter(&textImage);
		textPainter.setPen(QPen(Qt::black));
		textPainter.setFont(QFont("Times", 12, QFont::Bold));
		textPainter.drawText(textImage.rect(), Qt::AlignCenter, text);
		textPainter.end();
		GameObject* instructionText = new GameObject(name, placement, 0, scale, textImage, layer);
		return instructionText;
	}
signals:
	void pass();
	void fail();
};

#endif // QUEST_H
