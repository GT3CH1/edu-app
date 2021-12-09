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
	explicit FishVC(QWidget *parent = nullptr);
	~FishVC() override;

private:
	float const MODEL_SCALE = 20.0f;	// Used to scale game objects
	QSize const WINDOW_MIN = QSize(800, 600);	// Minimum window size
	QSize const CANVAS_MIN = QSize(720, 512);	// Minimum canvas size
	int const FPS = 17;	// Milliseconds between frames
	Ui::FishVC *ui;
	FishModel tutorialModel;
	QPointF viewToModel(QPointF);
	QPointF modelToView(QPointF);
	QTimer* mouseTimer;		// Controls the mouse held signal
	QPointF mousePosition;	// Tracks the last known mouse position
	float modelRatio;	// Used to scale game objects
	void resizeEvent(QResizeEvent*) override;

public slots:
	void renderGameObjects(std::vector<ObjectRenderInformation> renderables);
	void mouseClick(QPointF);
	void mouseMove(QPointF);
	void mouseRelease(QPointF);

private slots:
	void mouseHold();

signals:

	void mouseClickSignal(QPointF);		// Tells the model the mouse was clicked and where
	void mouseHoldSignal(QPointF);		// Tells the model the mouse is being held and where
	void mouseReleaseSignal(QPointF);	// Tells the model the mouse was released and where

};
#endif // FISHVC_H
