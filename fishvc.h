#ifndef FISHVC_H
#define FISHVC_H

#include <QMainWindow>
#include <fishmodel.h>

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
	Ui::FishVC *ui;
	FishModel tutorialModel;
//	QPoint modelToVisual(QPoint modelPos);
//	QPoint visualToModel(QPoint visualPos);

public slots:
	void renderGameObjects(QPoint, double, QImage);

signals:

};
#endif // FISHVC_H
