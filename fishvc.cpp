#include "fishvc.h"
#include "./ui_fishvc.h"
#include <Box2D/Box2D.h>
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

