#ifndef FISHVC_H
#define FISHVC_H

#include <QMainWindow>
#include <fishmodel.h>
#include <vector>
#include "objectrenderinformation.h"

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

public slots:
	void renderGameObjects(std::vector<ObjectRenderInformation> renderables);

signals:

};
#endif // FISHVC_H
