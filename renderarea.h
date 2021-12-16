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

private slots:
	void mouseMoveEvent(QMouseEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseDoubleClickEvent(QMouseEvent *);

signals:
	void mouseReleased(QPointF);
	void mousePressed(QPointF);
	void mouseLocation(QPointF);
};

#endif // RENDERAREA_H
