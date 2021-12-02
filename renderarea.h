#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QLabel>
#include <QMouseEvent>

class RenderArea : public QLabel
{
Q_OBJECT
public:
	RenderArea(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
	void setImage(QPixmap &);

private:
	float findMouseX(QMouseEvent *);
	float findMouseY(QMouseEvent *);

private slots:
	void mouseMoveEvent(QMouseEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseDoubleClickEvent(QMouseEvent *);

signals:
	void mouseReleased(float, float);
	void mousePressed(float, float);
	void mouseLocation(float, float);
};

#endif // RENDERAREA_H
