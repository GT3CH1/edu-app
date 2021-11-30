#include "fishvc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FishVC w;
	w.show();
	return a.exec();
}
