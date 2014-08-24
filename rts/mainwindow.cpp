#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include "QtMainGame.h"
#include "sidePanel.h"
#include "control.h"

MainWindow::MainWindow()
{
	control* ctrl = control::getInstance();
	glWidget = new QtMainGame;
	setMouseTracking(true);
	QApplication::desktop()->screenGeometry().height();
	glWidget->setMaximumWidth(QApplication::desktop()->screenGeometry().height()*1.5);
	sidePanel *sdPanel = sidePanel::getInstance();
	sdPanel->setMaximumWidth(220);
	sdPanel->setMinimumWidth(220);
	//sdPanel->setWindowOpacity(0);
	sdPanel->setUp();
	ctrl->setSidePanel(sdPanel);
    QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->heightForWidth(true);
	mainLayout->setContentsMargins(10,10,10,10);
	mainLayout->setSpacing(0);
    mainLayout->addWidget(glWidget,10);
	mainLayout->addWidget(sdPanel,2);
    setLayout(mainLayout);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{

    if (e->key() == Qt::Key_Escape) {

		
        exit(0);
	}
}
MainWindow::~MainWindow()
{
}

void MainWindow::updateGeom() {
	
	glWidget->setMainScreenPara(this->pos().x() + 8,this->pos().y() + 8,this->width(),this->height());
}

void MainWindow::resizeEvent(QResizeEvent *event) {
	updateGeom();
}