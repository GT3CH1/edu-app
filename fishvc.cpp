#include "fishvc.h"
#include "./ui_fishvc.h"

fishvc::fishvc(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::fishvc)
{
	ui->setupUi(this);
}

fishvc::~fishvc()
{
	delete ui;
}

