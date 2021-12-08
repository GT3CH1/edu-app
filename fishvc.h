#ifndef FISHVC_H
#define FISHVC_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <fishmodel.h>
#include <vector>
#include "objectrenderinformation.h"
#include <ui_fishvc.h>

QT_BEGIN_NAMESPACE
namespace Ui { class FishVC; }
QT_END_NAMESPACE

class FishVC : public QMainWindow
{
	Q_OBJECT

public:
	FishVC(QWidget *parent = nullptr);
	~FishVC();

private:
	float const MODEL_SCALE = 20.0f;	// Used to scale game objects
	int const FPS = 17;	// Milliseconds between frames
	Ui::FishVC *ui;
	FishModel tutorialModel;
	QPointF viewToModel(QPointF);
	QPointF modelToView(QPointF);
	QTimer* mouseTimer;		// Controls the mouse held signal
	QPointF mousePosition;	// Tracks the last known mouse position
	float modelRatio;	// Used to scale game objects

public slots:
	void renderGameObjects(std::vector<ObjectRenderInformation> renderables);
	void mouseClick(QPointF);
	void mouseMove(QPointF);
	void mouseRelease(QPointF);

private slots:
	void mouseHold();
	void canvasResized();

signals:
	void mouseClickSignal(QPointF);		// Tells the model the mouse was clicked and where
	void mouseHoldSignal(QPointF);		// Tells the model the mouse is being held and where
	void mouseReleaseSignal(QPointF);	// Tells the model the mouse was released and where

};
#endif // FISHVC_H
