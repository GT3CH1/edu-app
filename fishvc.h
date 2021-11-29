#ifndef FISHVC_H
#define FISHVC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class fishvc; }
QT_END_NAMESPACE

class fishvc : public QMainWindow
{
	Q_OBJECT

public:
	fishvc(QWidget *parent = nullptr);
	~fishvc();

private:
	Ui::fishvc *ui;
};
#endif // FISHVC_H
